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
#include "../cpp/linked-list-operations/intLinkedList.cpp"
#undef main

int main() {

    LinkedList list;
    list.deleteFirst(); list.deleteSecond(); CHECK(list.find(1) == nullptr);
    list.insert(1); list.deleteSecond(); CHECK(list.find(1)->info == 1);
    list.insert(2); list.insert(3);
    list.deleteSecond(); CHECK(list.find(2) == nullptr); CHECK(list.find(3)->next->info == 1);
    list.deleteFirst(); CHECK(list.find(3) == nullptr); CHECK(list.find(1) != nullptr);
    list.deleteFirst(); list.deleteFirst(); CHECK(list.find(1) == nullptr);
    for (int i = 0; i < 100; ++i) list.insert(i); // destructor checked by ASan/LSan

    return 0;
}
