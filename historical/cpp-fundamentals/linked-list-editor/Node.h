#pragma once
#include <string>
using namespace std;

class Node
{
private:
    string name;
    Node* next;
public:
    Node();
    Node(string theName, Node* nextNode);
    string getName();
    void setName(string newName);
    Node* getNext();
    void setNext(Node* newNext);
};