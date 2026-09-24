"""Check rank partitioning against independently computed minima."""
import os
from pathlib import Path
import random
import re
import subprocess
import sys

executable = str(Path(sys.argv[1]).resolve())
launcher = sys.argv[2]
environment = dict(os.environ, OMPI_MCA_rmaps_base_oversubscribe="1")
if hasattr(os, "geteuid") and os.geteuid() == 0:
    environment.update(OMPI_ALLOW_RUN_AS_ROOT="1", OMPI_ALLOW_RUN_AS_ROOT_CONFIRM="1")


def launch(ranks, args, expected=None):
    result = subprocess.run([launcher, "-n", str(ranks), executable, *map(str, args)],
                            env=environment, text=True, capture_output=True, timeout=20)
    if expected is None:
        assert result.returncode == 1, result.stdout + result.stderr
        assert "Usage: mpi_minimum" in result.stderr, result.stderr
        return
    assert result.returncode == 0, result.stdout + result.stderr
    values = re.search(r"serial_min=(-?\d+) parallel_min=(-?\d+)", result.stdout)
    assert values and tuple(map(int, values.groups())) == (expected, expected), result.stdout
    return result.stdout


checks = 0
for ranks, values in [(1, [8, -7, 4]), (2, [10, 9, 8, 7, -100]),
                      (3, [2000005, 2000004, 2000003, 2000002, 2000001]),
                      (8, [2147483647]), (4, [1, -2147483648]), (8, [5] * 17),
                      (11, [10, 9, 8, 7, 6, 5, 4, 3, 2, 1, -99])]:
    launch(ranks, ["--values", *values], min(values))
    checks += 1
rng = random.Random(17)
for ranks in [1, 2, 3, 5]:
    values = [rng.randrange(-2000000000, 2000000000) for _ in range(37)]
    launch(ranks, ["--values", *values], min(values))
    checks += 1
for ranks in [1, 3, 8]:
    state = 42
    values = []
    for _ in range(103):
        state = (state * 1664525 + 1013904223) & 0xffffffff
        values.append(state % 2000001 - 1000000)
    launch(ranks, [103, 42], min(values))
    checks += 1
for args in [[0], [-1], ["abc"], ["--values"], ["--values", "2147483648"], [10, 1, 2]]:
    launch(2, args)
    checks += 1

# Exercise the actual eight-million-element broadcast specified by the handout.
for seed, args in [(42, []), (7, ["--assignment", "7"])]:
    state = seed
    expected = 1000000001
    for _ in range(8000000):
        state = (state * 1664525 + 1013904223) & 0xffffffff
        expected = min(expected, state % 1000000001)
    output = launch(8, args, expected)
    assert "mode=assignment-broadcast count=8000000 ranks=8" in output, output
    checks += 1
for ranks, args in [(2, []), (8, ["--assignment", "bad-seed"])]:
    launch(ranks, args)
    checks += 1
print(f"Passed {checks} MPI scenarios.")
