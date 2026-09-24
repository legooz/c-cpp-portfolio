#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

enum RequestResult {
    REQUEST_INVALID = -3, REQUEST_EXCEEDS_CLAIM = -2, REQUEST_UNAVAILABLE = -1,
    REQUEST_UNSAFE = 0, REQUEST_GRANTED = 1
};

/* Tutorial 8 also describes the resource-request algorithm. A denied request
   leaves the original state unchanged, including after the tentative safety test. */
enum RequestResult bankers_request(BankerState *state, int process,
                                  const int request[RESOURCES], int sequence[PROCESSES]) {
    if (process < 0 || process >= PROCESSES || bankers_safe(state, sequence) < 0)
        return REQUEST_INVALID;
    for (int j = 0; j < RESOURCES; ++j) if (request[j] < 0) return REQUEST_INVALID;
    for (int j = 0; j < RESOURCES; ++j)
        if (request[j] > state->claim[process][j] - state->allocation[process][j])
            return REQUEST_EXCEEDS_CLAIM;
    for (int j = 0; j < RESOURCES; ++j)
        if (request[j] > state->available[j]) return REQUEST_UNAVAILABLE;
    BankerState trial = *state;
    for (int j = 0; j < RESOURCES; ++j) {
        trial.available[j] -= request[j];
        trial.allocation[process][j] += request[j];
    }
    if (bankers_safe(&trial, sequence) != 1) return REQUEST_UNSAFE;
    *state = trial;
    return REQUEST_GRANTED;
}

static bool parse_nonnegative(const char *token, int *value) {
    errno = 0;
    char *end;
    long parsed = strtol(token, &end, 10);
    if (errno || end == token || *end || parsed < 0 || parsed > INT_MAX) return false;
    *value = (int)parsed;
    return true;
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
    return parse_nonnegative(token, value);
}

int main(int argc, char **argv) {
    BankerState state;
    int sequence[PROCESSES];
    int process = 0, request[RESOURCES] = {0};
    if (argc != 1) {
        if (argc != 7 || strcmp(argv[1], "--request") != 0 ||
            !parse_nonnegative(argv[2], &process) || process < 1 || process > PROCESSES) {
            fputs("Usage: bankers [--request PROCESS(1..5) R1 R2 R3 R4]\n", stderr);
            return 1;
        }
        for (int j = 0; j < RESOURCES; ++j)
            if (!parse_nonnegative(argv[j + 3], &request[j])) goto invalid;
    }
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
    if (argc != 1) {
        enum RequestResult result = bankers_request(&state, process - 1, request, sequence);
        if (result == REQUEST_INVALID) goto invalid;
        if (result != REQUEST_GRANTED) {
            const char *reason = result == REQUEST_EXCEEDS_CLAIM ? "exceeds remaining claim" :
                                 result == REQUEST_UNAVAILABLE ? "resources unavailable" : "unsafe tentative state";
            printf("DENIED: %s.\n", reason);
            return 0;
        }
        puts("GRANTED: resources allocated safely.");
        safe = 1;
    }
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
