#include "LinkedList.h"
#include <iostream>

using namespace std;

LinkedList::LinkedList()
{
    head = nullptr;
    tail = nullptr;
}
LinkedList::~LinkedList()
{
    Node* temp = head;
    while (temp != nullptr)
    {
        Node* next = temp->getNext();
        delete temp;
        temp = next;
    }
}

Node* LinkedList::contains(string target) 
{
    Node* checkString = head;
    while (checkString != nullptr)
    {
        if (checkString->getName() == target)
        {
            
            
            cout << "contains: " << checkString->getName() << endl;
            //checkString->setName(nullptr);
            cout << "would you like to change the name? Y or N" << endl;
            char userChar = '0';
            cin >> userChar;
            if (userChar == 'Y')
            {
                string newname = "";
                cout << "Enter the new name " << endl;
                cin >> newname;
                checkString->setName(newname);
            }

            return checkString;
        }
        checkString = checkString->getNext();
    }
    return nullptr;
}


// Output everything in the list
void LinkedList::output()
{
    Node* temp = head;
    while (temp != nullptr)
    {
        cout << temp->getName() << endl;
        temp = temp->getNext();
    }
    cout << endl;
}

// Adds a new node with this string to the front of the linked list
void LinkedList::add(string s)
{
    if (head == nullptr)
    {
        // New list, make head point to it
        head = new Node(s, nullptr);
    }
    else
    {
        // Make a new node that points to head
        Node* temp = new Node(s, head);
        // Set head to the new node
        head = temp;
    }
}

void LinkedList::addTail(string s)
{

    Node* temp = head;
    
    while (temp->getNext() != nullptr)
    {
        temp = temp->getNext();
    }

    Node* addNodeTail = new Node(s, nullptr);
    temp->setNext(addNodeTail);
    tail = addNodeTail;

}
// Deletes first occurrence of s in the list
void LinkedList::remove(string s)
{
    Node* temp = head;
    Node* previous = nullptr;  // You might want to use this variable
    while (temp != nullptr)
    {
        if (temp->getName() == s)
        {
            // If we are deleting the head of the list
            if (temp == head)
            {
                head = head->getNext();
                delete temp;
            }
            else
                // We are deleting something that is not the head
            {
                previous->setNext(temp->getNext());
            }

            break;
        }
        previous = temp;
        temp = temp->getNext();
    }
}