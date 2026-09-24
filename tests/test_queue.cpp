#include <algorithm>
#include <array>
#include <climits>
#include <iostream>
#include <limits>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#define CHECK(condition) do { if (!(condition)) throw std::runtime_error("Check failed: " #condition); } while (false)
template<class Exception, class Function> void expectThrow(Function operation) {
    bool caught = false;
    try { operation(); } catch (const Exception&) { caught = true; }
    CHECK(caught);
}

#define main demo_main_0
#include "../cpp/queues/queue.cpp"
#undef main

int main() {

    Queue<int> queue;
    CHECK(queue.isEmpty());
    expectThrow<std::out_of_range>([&] { queue.front(); });
    expectThrow<std::out_of_range>([&] { queue.dequeue(); });
    for (int i = 0; i < 100; ++i) queue.enqueue(i);
    Queue<int> copy = queue;
    for (int i = 0; i < 100; ++i) { CHECK(queue.front() == i); CHECK(queue.dequeue() == i); }
    CHECK(queue.isEmpty()); CHECK(!copy.isEmpty()); copy.clear(); CHECK(copy.isEmpty());
    queue.enqueue(-1); CHECK(queue.dequeue() == -1);

    return 0;
}
