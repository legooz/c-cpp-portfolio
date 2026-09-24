#include <iostream>
using namespace std;

// IntNode definition
class IntNode
{
  public:
     IntNode();
     IntNode(int i, IntNode *in);
     int info;
     IntNode *next;
};

// IntNode implementation
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

// Linked List definition
class LinkedList
{
 public:
   LinkedList();
   ~LinkedList() { while (head) deleteFirst(); }
   LinkedList(const LinkedList&) = delete;
   LinkedList& operator=(const LinkedList&) = delete;
   void insert(int item);
   IntNode* find(int item);
   void deleteSecond();
   void deleteFirst(); // Declare the deleteFirst function
   void print();
 private:
   IntNode *head;
};

// Linked List implementation
LinkedList::LinkedList() : head(nullptr)
{
}

void LinkedList::insert(int item)
{
 IntNode *node = new IntNode(item);
 node->next = head;
 head = node;
}

IntNode* LinkedList::find(int item)
{
   IntNode *temp = head;
   while (temp != nullptr)
   {
        if (temp->info == item)
             return temp;
        temp = temp->next;
   }
   return nullptr;
}

void LinkedList::deleteSecond()
{
  if ((head != nullptr) && (head->next != nullptr))
  {
    IntNode* temp = head->next;
    head->next = temp->next;
    delete temp;
  }
}

void LinkedList::deleteFirst() // Implement the deleteFirst function
{
    if(head != nullptr)
    {
      IntNode* temp = head;
      head = temp->next;
      delete temp;
    }
}

void LinkedList::print()
{
   IntNode *temp = head;
   cout << endl;
   while (temp != nullptr)
   {
    cout << temp->info << " ";
    temp = temp->next;
   }
   cout << endl;
}

int main()
{
  LinkedList list;
  list.insert(10);
  list.insert(20);
  list.insert(30);

  cout << "Original list:" << endl;
  list.print();

  cout << "After deleting the first node:" << endl;
  list.deleteFirst();
  list.print();
    return 0;
}
