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
#include "../cpp/priority-queues/personQueue.cpp"
#undef main

int main() {

    std::priority_queue<Person> queue;
    queue.push(Person("long low priority name", -2));
    queue.push(Person("X", 100)); queue.push(Person("Y", 100)); queue.push(Person("Z", 0));
    CHECK(queue.top().priority == 100); queue.pop();
    CHECK(queue.top().priority == 100); queue.pop();
    CHECK(queue.top().priority == 0); queue.pop();
    CHECK(queue.top().priority == -2);

    return 0;
}
