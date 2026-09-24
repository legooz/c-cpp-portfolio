#pragma once
#include "queue.h"
#include <stdexcept>

template<class T> Queue<T>::Queue() = default;
template<class T> Queue<T>::~Queue() = default;
template<class T> void Queue<T>::clear() { lst.clear(); }
template<class T> bool Queue<T>::isEmpty() { return lst.empty(); }
template<class T> T Queue<T>::front() {
    if (lst.empty()) throw std::out_of_range("front of empty queue");
    return lst.front();
}
template<class T> T Queue<T>::dequeue() {
    if (lst.empty()) throw std::out_of_range("dequeue of empty queue");
    T item = lst.front();
    lst.pop_front();
    return item;
}
template<class T> void Queue<T>::enqueue(const T& item) { lst.push_back(item); }
