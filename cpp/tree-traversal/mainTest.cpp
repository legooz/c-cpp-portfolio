#include <iostream>

using namespace std;

// Define the Node class template directly in this file
template <typename T>
class Node {
private:
    T item;
    Node<T>* left;
    Node<T>* right;

public:
    Node(T value) : item(value), left(nullptr), right(nullptr) {}

    Node<T>* getLeft() const { return left; }
    Node<T>* getRight() const { return right; }
    T getItem() const { return item; }

    void setLeft(Node<T>* node) { left = node; }
    void setRight(Node<T>* node) { right = node; }
};

template <typename T> void preOrder(Node<T>* n) {
    if (!n) return;
    cout << n->getItem() << " "; preOrder(n->getLeft()); preOrder(n->getRight());
}
template <typename T> void inOrder(Node<T>* n) {
    if (!n) return;
    inOrder(n->getLeft()); cout << n->getItem() << " "; inOrder(n->getRight());
}
template <typename T> void postOrder(Node<T>* n) {
    if (!n) return;
    postOrder(n->getLeft()); postOrder(n->getRight()); cout << n->getItem() << " ";
}

int main()
{
  Node<int> root(5);
  Node<int> n1(3);
  Node<int> n2(2);
  Node<int> n3(5);
  Node<int> n4(7);
  Node<int> n5(8);
  root.setLeft(&n1); root.setRight(&n4);
  n1.setLeft(&n2); n1.setRight(&n3);
  n4.setRight(&n5);

  preOrder(&root); cout << endl;
  inOrder(&root); cout << endl;
  postOrder(&root); cout << endl;

  return 0;
    return 0;
}
