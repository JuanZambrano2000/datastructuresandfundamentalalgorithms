#ifndef _BST_H_
#define _BST_H_

#include "BSTNode.h"
#include "QueueLinkedList.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

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
  int auxHeight(BSTNode<T> *p);
  bool auxAncestors(BSTNode<T> *p, T value);
  int getLevelUtil(BSTNode<T>* node, T data, int level);

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
  // to-do
  void visit(int opcion);
  int height();
  void ancestors(T value);
  int whatlevelamI(T data);
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

template <class T> void BST<T>::levelByLevel() {
  std::cout << "levelByLevel():" << std::endl;
  auxiliarLevelByLevel(root);
  std::cout << std::endl;
}

// Funcion simple que simplemente de acuerdo a la opcion ingresada por el
// usuario llama al algoritmo de orden.
template <class T> void BST<T>::visit(int opcion) {
  if (opcion == 1) {
    preorder();
  } else if (opcion == 2) {
    inorder();
  } else if (opcion == 3) {
    postorder();
  } else if (opcion == 4) {
    levelByLevel();
  } else {
    throw std::out_of_range("Opcion fuera del rango");
  }
}

// Nos basamos en la explicacion y pseudocodigo para entenderlo de la pagina:
// https://www.baeldung.com/cs/binary-tree-height Pasamos un apuntador a root,
// si el arbol esta vacio su altura es de 0, si no viajamos a cada nodo posible,
// la rama que sea mas larga sera nuestro max y el valor que regresemos, la
// complejidad en un arbol vacio seria de O(1), en el caso promedio como
// calculamos la altura de cada nodo seria de O(n)
template <class T> int BST<T>::auxHeight(BSTNode<T> *p) {
  //Cuando el nodo está vacío regersa una altura de 0
  if (p == nullptr)
    return 0;
  else {
    int leftHeight = auxHeight(p->left);
    int rightHeight = auxHeight(p->right);
    return std::max(leftHeight, rightHeight) + 1;
  }
}

// Funcion auxiliar que llama a la funcion que calcula la altura del arbol
template <class T> int BST<T>::height() { return auxHeight(root); }

//Función que llama a la verdadera función ancestro
template <class T> void BST<T>::ancestors(T value) {
  auxAncestors(root, value);
}

// Complejidad O(n) ya que recorre los nodos necesarios de la lista.
template <class T> bool BST<T>::auxAncestors(BSTNode<T> *p, T value) {
  // sale en false si no hay nada en el nodo actualmente en cuestión
  if (p == nullptr) {
    return false;
  }
  // Sale en true cuando encuentra el valor
  if (p->data == value) {
    return true;
  }
  // Sale en true cuando encuentra el valor en algún nodo después del actual
  if (auxAncestors(p->left, value) || auxAncestors(p->right, value)) {
    std::cout << p->data << std::endl;
    return true;
  }
  // Sale en false si no logra ninguna condición
  return false;
}

// Helper function for getLevel(). It returns level of the
// data if data is present in tree, otherwise returns 0.
template <class T>
int BST<T>::getLevelUtil(BSTNode<T>* node, T data, int level) {
    if (node == nullptr)
        return 0;
    if (node->data == data)
        return level;
    int downlevel
        = getLevelUtil(node->left, data, level + 1);
    if (downlevel != 0)
        return downlevel;
 
    downlevel = getLevelUtil(node->right, data, level + 1);
    return downlevel;
}

template <class T>
int BST<T>::whatlevelamI(T data) {
    return getLevelUtil(root, data, 1)-1;
}

#endif // _BST_H_
