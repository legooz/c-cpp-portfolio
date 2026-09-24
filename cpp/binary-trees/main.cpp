#include <iostream>
using namespace std;

#include "node.cpp"

template<typename T>
void printInOrder(Node<T>* node) {
    if (node == nullptr) return;
    printInOrder(node->getLeft());
    cout << node->getItem() << " ";
    printInOrder(node->getRight());
}

int main() {
    Node<int> *root = new Node<int>(10);
    Node<int> *leftChild = new Node<int>(5);
    Node<int> *rightChild = new Node<int>(15);

    // Linking nodes to form a tree.
    root->setLeft(leftChild);
    root->setRight(rightChild);

    cout << "Inorder Traversal of the Tree: ";
    printInOrder(root);
    cout << endl;

    // Cleanup to avoid memory leaks.
    delete root;
    delete leftChild;
    delete rightChild;

    return 0;
    return 0;
}
