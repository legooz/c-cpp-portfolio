#include <string>
#include "Node.h"
using namespace std;

Node::Node() : name(""), next(nullptr)
{
}

Node::Node(string theName, Node* nextNode) :
    name(theName), next(nextNode)
{
}
string Node::getName()
{
    return name;
}
void Node::setName(string newName)
{
    name = newName;
}
Node* Node::getNext()
{
    return next;
}
void Node::setNext(Node* newNext)
{
    next = newNext;
}