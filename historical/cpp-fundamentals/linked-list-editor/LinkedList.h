#pragma once
#include "Node.h"
#include <string>
using namespace std;

class LinkedList
{
private:
    Node* head;// Points to the first thing in the list
    Node* tail;
public:
    LinkedList();
    ~LinkedList();
    Node* contains(string target);
    void add(string s); // Adds to front of list
    void addTail(string s);
    void remove(string s); // Deletes first occurrence of s in the list
    void output();  // Output everything in the list
};