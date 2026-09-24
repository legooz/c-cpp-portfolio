#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum { PROCESSES = 5, RESOURCES = 4 };
typedef struct {
    int claim[PROCESSES][RESOURCES];
    int allocation[PROCESSES][RESOURCES];
    int available[RESOURCES];
} BankerState;

/* Returns 1 for safe, 0 for unsafe, -1 for invalid resources.
   The input is never modified. sequence is populated for completed processes. */
int bankers_safe(const BankerState *state, int sequence[PROCESSES]) {
    long long work[RESOURCES];
    bool finished[PROCESSES] = {false};
    int completed = 0;
    for (int j = 0; j < RESOURCES; ++j) {
        if (state->available[j] < 0) return -1;
        work[j] = state->available[j];
        for (int i = 0; i < PROCESSES; ++i) {
            if (state->allocation[i][j] < 0 ||
                state->claim[i][j] < state->allocation[i][j]) return -1;
        }
    }
    bool progress;
    do {
        progress = false;
        for (int i = 0; i < PROCESSES; ++i) {
            if (finished[i]) continue;
            int j = 0;
            while (j < RESOURCES &&
                   state->claim[i][j] - state->allocation[i][j] <= work[j]) ++j;
            if (j == RESOURCES) {
                for (int k = 0; k < RESOURCES; ++k) work[k] += state->allocation[i][k];
                finished[i] = true;
                sequence[completed++] = i;
                progress = true;
            }
        }
    } while (progress && completed < PROCESSES);
    return completed == PROCESSES;
}

static bool read_nonnegative(int *value) {
    char token[64];
    size_t length = 0;
    int ch;
    do { ch = getchar(); } while (ch != EOF && isspace((unsigned char)ch));
    if (ch == EOF) return false;
    do {
        if (length == sizeof(token) - 1) return false;
        token[length++] = (char)ch;
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));
    token[length] = '\0';
    errno = 0;
    char *end;
    long parsed = strtol(token, &end, 10);
    if (errno || *end || parsed < 0 || parsed > INT_MAX) return false;
    *value = (int)parsed;
    return true;
}

int main(void) {
    BankerState state;
    int sequence[PROCESSES];
    /* Input: 20 claims, 20 allocations, then 4 available counts, row-major. */
    for (int i = 0; i < PROCESSES; ++i)
        for (int j = 0; j < RESOURCES; ++j)
            if (!read_nonnegative(&state.claim[i][j])) goto invalid;
    for (int i = 0; i < PROCESSES; ++i)
        for (int j = 0; j < RESOURCES; ++j)
            if (!read_nonnegative(&state.allocation[i][j])) goto invalid;
    for (int j = 0; j < RESOURCES; ++j)
        if (!read_nonnegative(&state.available[j])) goto invalid;
    int ch;
    while ((ch = getchar()) != EOF) if (!isspace((unsigned char)ch)) goto invalid;
    int safe = bankers_safe(&state, sequence);
    if (safe < 0) goto invalid;
    if (safe) {
        printf("SAFE sequence:");
        for (int i = 0; i < PROCESSES; ++i) printf(" P%d", sequence[i] + 1);
        putchar('\n');
    } else {
        puts("UNSAFE: no complete safe sequence exists.");
    }
    return 0;
invalid:
    fputs("Expected 44 nonnegative integers; allocation must not exceed claim.\n", stderr);
    return 1;
}
