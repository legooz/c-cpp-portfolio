#pragma once
#include <iostream>
#include "node.h"

template<class T>
Node<T>::Node() : item{}
{
 left = nullptr;
 right = nullptr;
 parent = nullptr;
}

template<class T>
Node<T>::Node(T item) : item(item)
{
 left = nullptr;
 right = nullptr;
 parent = nullptr;
}

template<class T>
Node<T>::~Node()
{
}

template<class T>
Node<T>* Node<T>::getLeft()
{
  return left;
}

template<class T>
Node<T>* Node<T>::getRight()
{
  return right;
}

template<class T>
Node<T>* Node<T>::getParent()
{
  return parent;
}

template<class T>
void Node<T>::setLeft(Node *n)
{
  if (left && left->parent == this) left->parent = nullptr;
  left = n;
  if (n) n->parent = this;
}

template<class T>
void Node<T>::setRight(Node *n)
{
  if (right && right->parent == this) right->parent = nullptr;
  right = n;
  if (n) n->parent = this;
}

template<class T>
void Node<T>::setParent(Node *n)
{
  parent = n;
}

template<class T>
T& Node<T>::getItem()
{
  return item;
}
