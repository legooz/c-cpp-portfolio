#include <errno.h>
#include <limits.h>
#include <mpi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int parse_int(const char *text, int *value) {
    char *end;
    errno = 0;
    long parsed = strtol(text, &end, 10);
    if (errno || end == text || *end || parsed < INT_MIN || parsed > INT_MAX) return 0;
    *value = (int)parsed;
    return 1;
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int rank, ranks;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &ranks);
    int count = 100003, seed = 42, valid = 1;
    const int explicit_values = argc > 1 && strcmp(argv[1], "--values") == 0;
    if (explicit_values) count = argc - 2;
    else {
        if (argc > 3) valid = 0;
        if (argc > 1 && !parse_int(argv[1], &count)) valid = 0;
        if (argc > 2 && !parse_int(argv[2], &seed)) valid = 0;
    }
    if (count < 1 || count > 10000000) valid = 0;
    int *array = NULL, *counts = NULL, *offsets = NULL;
    int serial_min = INT_MAX;
    if (rank == 0 && valid) {
        array = malloc((size_t)count * sizeof(*array));
        counts = malloc((size_t)ranks * sizeof(*counts));
        offsets = malloc((size_t)ranks * sizeof(*offsets));
        if (!array || !counts || !offsets) { fputs("Allocation failed.\n", stderr); MPI_Abort(MPI_COMM_WORLD, 1); }
        uint32_t state = (uint32_t)seed;
        for (int i = 0; i < count; ++i) {
            if (explicit_values) {
                if (!parse_int(argv[i + 2], &array[i])) { valid = 0; break; }
            } else {
                state = state * UINT32_C(1664525) + UINT32_C(1013904223);
                array[i] = (int)(state % UINT32_C(2000001)) - 1000000;
            }
            if (array[i] < serial_min) serial_min = array[i];
        }
        int offset = 0;
        for (int r = 0; r < ranks; ++r) {
            counts[r] = count / ranks + (r < count % ranks);
            offsets[r] = offset;
            offset += counts[r];
        }
    }
    MPI_Bcast(&valid, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (!valid) {
        if (rank == 0) fputs("Usage: mpi_minimum [size (1..10000000) [seed]] | --values INT...\n", stderr);
        free(array); free(counts); free(offsets);
        MPI_Finalize();
        return 1;
    }
    const int local_count = count / ranks + (rank < count % ranks);
    int *local = malloc((size_t)(local_count > 0 ? local_count : 1) * sizeof(*local));
    if (!local) { fputs("Local allocation failed.\n", stderr); MPI_Abort(MPI_COMM_WORLD, 1); }
    MPI_Scatterv(array, counts, offsets, MPI_INT, local, local_count, MPI_INT, 0, MPI_COMM_WORLD);
    int local_min = INT_MAX, parallel_min;
    for (int i = 0; i < local_count; ++i) if (local[i] < local_min) local_min = local[i];
    MPI_Reduce(&local_min, &parallel_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    int result = 0;
    if (rank == 0) {
        printf("count=%d ranks=%d serial_min=%d parallel_min=%d\n", count, ranks, serial_min, parallel_min);
        result = parallel_min != serial_min;
    }
    MPI_Bcast(&result, 1, MPI_INT, 0, MPI_COMM_WORLD);
    free(local); free(array); free(counts); free(offsets);
    MPI_Finalize();
    return result;
}
