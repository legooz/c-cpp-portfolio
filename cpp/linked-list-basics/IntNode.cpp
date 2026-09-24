#include <iostream>
using namespace std;

class IntNode
{
  public:
     IntNode();
     IntNode(int i, IntNode *in);
     int info;
     IntNode *next;
};

IntNode::IntNode()
{
  info = 0;
  next = nullptr;
}

IntNode::IntNode(int i, IntNode *nextNode = nullptr)
{
    info = i;
    next = nextNode;
}
