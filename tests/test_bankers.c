#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define main bankers_demo_main
#include "../c/bankers/bankers_algorithm.c"
#undef main
#define CHECK(condition) do { if (!(condition)) { fputs("Failed: " #condition "\n", stderr); exit(1); } } while (0)

int main(void) {
    const BankerState initial = {
        {{7,5,3,0}, {3,2,2,0}, {9,0,2,0}, {2,2,2,0}, {4,3,3,0}},
        {{0,1,0,0}, {2,0,0,0}, {3,0,2,0}, {2,1,1,0}, {0,0,2,0}},
        {3,3,2,0}
    };
    BankerState state = initial;
    int sequence[PROCESSES];
    CHECK(bankers_safe(&state, sequence) == 1);
    const int grant[] = {1,0,2,0};
    CHECK(bankers_request(&state, 1, grant, sequence) == REQUEST_GRANTED);
    CHECK(state.available[0] == 2 && state.available[2] == 0);
    CHECK(state.allocation[1][0] == 3 && state.allocation[1][2] == 2);
    CHECK(bankers_safe(&state, sequence) == 1);
    state = initial;
    const int unsafe[] = {3,3,0,0};
    CHECK(bankers_request(&state, 4, unsafe, sequence) == REQUEST_UNSAFE);
    CHECK(memcmp(&state, &initial, sizeof(state)) == 0);
    const int exceeds[] = {2,0,0,0};
    CHECK(bankers_request(&state, 1, exceeds, sequence) == REQUEST_EXCEEDS_CLAIM);
    const int unavailable[] = {7,0,0,0};
    CHECK(bankers_request(&state, 0, unavailable, sequence) == REQUEST_UNAVAILABLE);
    const int invalid[] = {-1,0,0,0};
    CHECK(bankers_request(&state, 0, invalid, sequence) == REQUEST_INVALID);
    const int zero[] = {0,0,0,0};
    CHECK(bankers_request(&state, 5, zero, sequence) == REQUEST_INVALID);
    CHECK(memcmp(&state, &initial, sizeof(state)) == 0);
    CHECK(bankers_request(&state, 0, zero, sequence) == REQUEST_GRANTED);
    CHECK(memcmp(&state, &initial, sizeof(state)) == 0);
    return 0;
}
