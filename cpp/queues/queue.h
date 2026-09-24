#pragma once
#include <list>
using std::list;

template<class T>
class Queue
{
public:
    Queue();
    ~Queue();
    void clear();
    bool isEmpty();
    T front();
    T dequeue();
    void enqueue(const T& el);
private:
    list<T> lst;
};
