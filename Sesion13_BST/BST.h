#ifndef _BST_H_
#define _BST_H_

#include "BSTNode.h"
#include "QueueLinkedList.h"
#include <iostream>

template <class T> class BST {
private:
  BSTNode<T> *root;
  void clearMemory(BSTNode<T> *p);
  BSTNode<T> *insertRecursive(BSTNode<T> *p, T value);
  BSTNode<T> *deleteRecursive(BSTNode<T> *p, T value);
  BSTNode<T> *getSuccessor(BSTNode<T> *p);
  void print2D(BSTNode<T> *p, int space);
  void recursiveInorder(BSTNode<T> *p);
  void recursivePostorder(BSTNode<T> *p);
  void recursivePreorder(BSTNode<T> *p);
  void auxiliarLevelByLevel(BSTNode<T> *p);

public:
  BST();
  ~BST();
  bool search(T value);
  void insert(T value);
  void deleteNode(T value);
  void print();
  void inorder();
  void postorder();
  void preorder();
  void levelByLevel();

};

template <class T> BST<T>::BST() {
  std::cout << "---> Creando un BST vacio: " << this << std::endl;
  root = nullptr;
}

template <class T> BST<T>::~BST() {
  // std::cout << "---> Liberando memoria del BinarySearchTree: " << this <<
  // std::endl;
  clearMemory(root);
}

template <class T> void BST<T>::clearMemory(BSTNode<T> *p) {
  if (p != nullptr) {
    clearMemory(p->left);
    clearMemory(p->right);
    delete p;
    p = nullptr;
  }
}

template <class T> bool BST<T>::search(T value) {
  BSTNode<T> *p = root;
  while (p != nullptr) {
    if (p->data == value)
      return true;
    else
      p = (value < p->data) ? p->left : p->right;
  }
  return false;
}

template <class T> BSTNode<T> *BST<T>::insertRecursive(BSTNode<T> *p, T value) {
  if (p == nullptr) // El BST esta vacio
    p = new BSTNode<T>(value);
  else if (value < p->data) // insercion a la izquierda
    p->left = insertRecursive(p->left, value);
  else if (value > p->data) // insercion a la derecha
    p->right = insertRecursive(p->right, value);
  else
    std::cout << "El elemento " << value << " ya existe en el BST" << std::endl;
  return p;
}

template <class T> void BST<T>::insert(T value) {
  root = insertRecursive(root, value);
}

template <class T> BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *p) {
  BSTNode<T> *current = p;
  while (current && current->left != nullptr) {
    current = current->left;
  }
  return current;
}

template <class T> BSTNode<T> *BST<T>::deleteRecursive(BSTNode<T> *p, T value) {
  BSTNode<T> *current = p;
  // caso base, arbol BST vacio
  if (p == nullptr)
    return p;
  if (value < p->data)
    p->left = deleteRecursive(p->left, value);
  else if (value > p->data)
    p->right = deleteRecursive(p->right, value);
  else { // localizamos el nodo a borrar
    // Caso 1: El nodo a borrar no tiene hijos
    if (p->left == nullptr && p->right == nullptr) {
      delete p;
      p = nullptr;
      return p;
    } // Caso 2: El nodo a borrar solo tiene un hijo
    else if (p->left == nullptr) { // tiene solo hijo derecho
      current = p->right;
      delete p;
      p = nullptr;
      return current;
    } else if (p->right == nullptr) { // tiene solo hijo izquierdo
      current = p->left;
      delete p;
      p = nullptr;
      return current;
    }
    // Caso 3: El nodo a borrar tiene dos hijos
    current = getSuccessor(p->right);
    p->data = current->data;
    p->right = deleteRecursive(p->right, current->data);
  }
  return p;
}

template <class T> void BST<T>::deleteNode(T value) {
  root = deleteRecursive(root, value);
}

template <class T> void BST<T>::print2D(BSTNode<T> *root, int space) {
  // Caso base
  if (root == nullptr)
    return;
  // Incrementa la distancia entre niveles
  space += 5;

  // Procesa hijo derecho
  print2D(root->right, space);
  // Imprime el nodo actual despues de los espacios necesarios
  std::cout << std::endl;
  for (int i = 5; i < space; i++)
    std::cout << " ";
  std::cout << root->data << std::endl;
  // Procesa el hijo izquierdo
  print2D(root->left, space);
}

template <class T> void BST<T>::print() { print2D(root, 0); }

template <class T> void BST<T>::recursiveInorder(BSTNode<T> *p) {
  if (p != nullptr) {
    recursiveInorder(p->left);
    std::cout << p->data << " ";
    recursiveInorder(p->right);
  }
}

template <class T> void BST<T>::inorder() {
  std::cout << "inorder():" << std::endl;
  recursiveInorder(root);
  std::cout << std::endl;
}

template <class T> void BST<T>::recursivePreorder(BSTNode<T> *p) {
  if (p != nullptr) {
    std::cout << p->data << " ";
    recursiveInorder(p->left);
    recursiveInorder(p->right);
  }
}

template <class T> void BST<T>::preorder() {
  std::cout << "preorder():" << std::endl;
  recursivePreorder(root);
  std::cout << std::endl;
}

template <class T> void BST<T>::recursivePostorder(BSTNode<T> *p) {
  if (p != nullptr) {
    recursivePostorder(p->left);
    recursivePostorder(p->right);
    std::cout << p->data << " ";
  }
}

template <class T> void BST<T>::postorder() {
  std::cout << "postorder():" << std::endl;
  recursivePostorder(root);
  std::cout << std::endl;
}

template <class T> void BST<T>::auxiliarLevelByLevel(BSTNode<T> *p) {
  QueueLinkedList<BSTNode<T> *> fila;
  fila.enqueue(p);
  while (!fila.isEmpty()) {
    BSTNode<T> *q = fila.getFront();
    fila.dequeue();
    std::cout << q->data << " ";
    if (q->left != nullptr)
      fila.enqueue(q->left);
    if (q->right != nullptr)
      fila.enqueue(q->right);
  }
}

template <class T> 
void BST<T>::levelByLevel() {
  std::cout << "levelByLevel():" << std::endl;
  auxiliarLevelByLevel(root);
  std::cout << std::endl;
}




#endif // _BST_H_
