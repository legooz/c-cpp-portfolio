"""Exercise the built programs, including malformed input and process lifecycles."""
from collections import Counter
from itertools import permutations
from pathlib import Path
import random
import re
import subprocess
import sys
import tempfile
import unittest

BIN = Path(sys.argv.pop(1)).resolve()


def run(name, *args, data="", code=0):
    result = subprocess.run([str(BIN / name), *map(str, args)], input=data,
                            text=True, capture_output=True, timeout=15)
    if result.returncode != code:
        raise AssertionError(f"{name}: expected exit {code}, got {result.returncode}\n{result.stdout}\n{result.stderr}")
    return result.stdout


class Programs(unittest.TestCase):
    def test_bankers_against_exhaustive_oracle(self):
        rng = random.Random(42)
        saw_safe = saw_unsafe = False
        for _ in range(60):
            allocation = [[rng.randrange(4) for _ in range(4)] for _ in range(5)]
            need = [[rng.randrange(6) for _ in range(4)] for _ in range(5)]
            claim = [[a + b for a, b in zip(row, n)] for row, n in zip(allocation, need)]
            available = [rng.randrange(4) for _ in range(4)]

            def valid_order(order):
                work = available[:]
                for i in order:
                    if any(n > w for n, w in zip(need[i], work)):
                        return False
                    work = [w + a for w, a in zip(work, allocation[i])]
                return True

            expected = any(valid_order(order) for order in permutations(range(5)))
            saw_safe |= expected
            saw_unsafe |= not expected
            tokens = [str(v) for matrix in (claim, allocation) for row in matrix for v in row]
            output = run("bankers", data=" ".join(tokens + list(map(str, available))))
            self.assertEqual(output.startswith("SAFE"), expected)
            if expected:
                order = [int(n) - 1 for n in re.findall(r"P(\d+)", output)]
                self.assertEqual(sorted(order), list(range(5)))
                self.assertTrue(valid_order(order))
        self.assertTrue(saw_safe and saw_unsafe)

    def test_bankers_invalid_and_boundaries(self):
        self.assertTrue(run("bankers", data="0 " * 44).startswith("SAFE"))
        self.assertTrue(run("bankers", data="2147483647 " * 44).startswith("SAFE"))
        for data in ("", "x", "0 " * 43, "0 " * 45, "-1 " + "0 " * 43,
                     "2147483648 " + "0 " * 43, "1" * 1000, "0 " * 44 + "garbage",
                     "0 " * 20 + "1 " + "0 " * 23):
            run("bankers", data=data, code=1)

    @unittest.skipUnless((BIN / "process_info").exists(), "POSIX only")
    def test_process_exit_and_wait(self):
        output = run("process_info")
        parent = re.search(r"Parent PID: (\d+); child PID: (\d+)", output)
        child = re.search(r"Child PID: (\d+); parent PID: (\d+)", output)
        self.assertIsNotNone(parent)
        self.assertIsNotNone(child)
        self.assertEqual(parent.groups(), tuple(reversed(child.groups())))
        run("process_info", "/bin/sh", "-c", "exit 7", code=7)
        run("process_info", "/this-command-does-not-exist", code=127)
        run("process_info", "/bin/sh", "-c", "kill -TERM $$", code=143)

    @unittest.skipUnless((BIN / "threads_with_semaphore").exists(), "POSIX only")
    def test_thread_output(self):
        message = "output--------------------output\n"
        for _ in range(10):
            self.assertEqual(run("threads_with_semaphore"), message * 20)
            # Character-level stdio is safe, but a complete message isn't atomic.
            # Interleaving is allowed, never required by a scheduler.
            self.assertEqual(Counter(run("threads_without_semaphore")), Counter(message * 20))

    def test_files(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "sample.txt"
            path.write_text("1239 -9871 +00021 0 10000 3 4 5 6 7 8\n")
            output = run("leading_digits", path)
            expected = {str(i): (2 if i == 1 else 1) for i in range(1, 10)}
            actual = dict((a, int(b)) for a, b in re.findall(r"^(\d): (\d+)$", output, re.M))
            self.assertEqual(actual, expected)
            self.assertIn("Zero values omitted: 1", output)
            path.write_text("12invalid")
            run("leading_digits", path, code=1)
            path.write_text("")
            self.assertIn("1: 0", run("leading_digits", path))
            path.write_text("AEIOU\ncat\nboat\n")
            self.assertEqual(run("vowel_runs", path), "AEIOU (5 consecutive vowels)\n")
            path.write_text("")
            run("vowel_runs", path, code=1)
            run("vowel_runs", Path(tmp) / "missing", code=1)
            run("leading_digits", Path(tmp) / "missing", code=1)

    def test_palindrome_input(self):
        self.assertIn("racecar is a palindrome.", run("palindrome", data="racecar n\n"))
        self.assertIn("abc is not a palindrome.", run("palindrome", data="abc n\n"))
        self.assertIn("is a palindrome.", run("palindrome", data="x" * 10000 + " n\n"))
        run("palindrome", code=1)

    def test_hamming_input(self):
        self.assertIn("Hamming distance: 32", run("hamming_distance", data="0 4294967295"))
        self.assertIn("Hamming distance: 0", run("hamming_distance", data="42 42"))
        for data in ("", "abc 1", "1", "-1 0", "4294967296 0", "123garbage 0"):
            run("hamming_distance", data=data, code=1)

    def test_demonstrations(self):
        self.assertEqual(run("pair_operators").split(), ["5", "10", "1", "2", "6", "12", "8", "14"])
        self.assertIn("110100101000101011000010011", run("zipcode_codec"))
        self.assertEqual(run("insertion_sort").split(), ["2", "3", "5", "7", "8", "10"])
        self.assertEqual(run("recursive_sorted").split(), ["1", "0"])
        self.assertIn("First Node: 10\nSecond Node: 8", run("linked_list_basics"))
        self.assertIn("20 10", run("linked_list_operations"))
        self.assertEqual(run("queues").split(), ["Bill", "Aaron", "Zorro", "Gobu"])
        self.assertTrue(run("priority_queues").startswith("CEO 1000\n"))
        self.assertIn("5 10 15", run("binary_trees"))
        self.assertEqual(run("tree_traversal").splitlines(), ["5 3 2 5 7 8 ", "2 3 5 5 7 8 ", "2 5 3 8 7 5 "])
        self.assertIn("491: Attack at dawn!!", run("word_cipher"))
        self.assertIn("Shuffled Playlist:", run("playlist"))
        run("selection_sort")
        output = run("movie_sort").split("After sorting")[1]
        names = [line.split(", ")[0] for line in output.splitlines() if ", " in line]
        self.assertEqual(names, sorted(names))
        self.assertEqual(len(names), 6)
        self.assertEqual(len(run("maze_generation").splitlines()), 41)
        run("maze_search")
        run("maze_class")


if __name__ == "__main__":
    unittest.main()
