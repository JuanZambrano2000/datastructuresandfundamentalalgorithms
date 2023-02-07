#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include <iostream>
#include "AVLNode.h"
#include "QueueLinkedList.h"

template <class T>
class AVLTree {
  private:
    AVLNode<T> *root;
    void clearMemory(AVLNode<T> *p);
    void print2D(AVLNode<T> *p, int space);
    void recursiveInorder(AVLNode<T> *p);
    void recursivePostorder(AVLNode<T> *p);
    void recursivePreorder(AVLNode<T> *p);
    void auxiliarLevelByLevel(AVLNode<T> *p);

    // AVL Tree methods
    int height(AVLNode<T> *node);
    int max(int a, int b);
    int getBalance(AVLNode<T> *node);
    AVLNode<T> *rightRotate(AVLNode<T> *y);
    AVLNode<T> *leftRotate(AVLNode<T> *x);
    AVLNode<T> *insertRecursive(AVLNode<T> *p, T value);
    AVLNode<T> *deleteRecursive(AVLNode<T> *p, T value);
    AVLNode<T> *getSuccessor(AVLNode<T> *p);
    
    
  public:
    AVLTree();
    ~AVLTree();
    void print();
    void inorder();
    void postorder();
    void preorder();
    void levelByLevel();

    // AVL Tree methods
    bool search(T value);
    void insert(T value);
    void remove(T value);
    
};

template <class T>
AVLTree<T>::AVLTree() {
  //std::cout << "---> Creando un AVL Tree vacio: " << this  << std::endl;
  root = nullptr;
}

template <class T>
AVLTree<T>::~AVLTree() {
  //std::cout << "---> Liberando memoria del AVL Tree: " << this << std::endl;
  clearMemory(root);
}

template <class T>
void AVLTree<T>::clearMemory(AVLNode<T> *p) {
  if (p != nullptr) {
    clearMemory(p->left);
    clearMemory(p->right);
    delete p;
    p = nullptr;
  }
}

template <class T>
void AVLTree<T>::print2D(AVLNode<T> *root, int space) {
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

template <class T>
void AVLTree<T>::print() {
    print2D(root, 0);
}

template <class T>
void AVLTree<T>::recursiveInorder(AVLNode<T> *p) {
  if (p != nullptr) {
    recursiveInorder(p->left);
    std::cout << p->data << " ";
    recursiveInorder(p->right);
  }
}

template <class T>
void AVLTree<T>::inorder() {
    std::cout << "inorder():" << std::endl;
    recursiveInorder(root);
    std::cout << std::endl;
}

template <class T>
void AVLTree<T>::recursivePreorder(AVLNode<T> *p) {
  if (p != nullptr) {
    std::cout << p->data << " ";
    recursiveInorder(p->left);
    recursiveInorder(p->right);
  }  
}

template <class T>
void AVLTree<T>::preorder() {
    std::cout << "preorder():" << std::endl;
    recursivePreorder(root);
    std::cout << std::endl;
}

template <class T>
void AVLTree<T>::recursivePostorder(AVLNode<T> *p) {
  if (p != nullptr) {
    recursivePostorder(p->left);
    recursivePostorder(p->right);
    std::cout << p->data << " ";
  }
}

template <class T>
void AVLTree<T>::postorder() {
    std::cout << "postorder():" << std::endl;
    recursivePostorder(root);
    std::cout << std::endl;
}

template <class T>
void AVLTree<T>::auxiliarLevelByLevel(AVLNode<T> *p) {
  QueueLinkedList<AVLNode<T> *> fila;
  fila.enqueue(p);
  while (!fila.isEmpty()) {
    AVLNode<T> *q  = fila.getFront();
    fila.dequeue();
    std::cout << q->data << " ";
    if (q->left != nullptr) fila.enqueue(q->left);
    if (q->right != nullptr) fila.enqueue(q->right);
  }  
}

template <class T>
void AVLTree<T>::levelByLevel() {
    std::cout << "levelByLevel():" << std::endl;
    auxiliarLevelByLevel(root);
    std::cout << std::endl;
}

template <class T>
bool AVLTree<T>::search(T value) {
  AVLNode<T> *p = root;
  while (p != nullptr) {
    if (p->data == value) 
      return true;
    else
      p = (value < p->data) ? p->left : p->right;
  }
  return false;
}

template <class T>
int AVLTree<T>::height(AVLNode<T> *node) {
  if (node == nullptr) 
    return 0;
  return node->height;
}

template <class T>
int AVLTree<T>::max(int a, int b) {
  return (a > b) ? a : b;
}

template <class T>
int AVLTree<T>::getBalance(AVLNode<T> *node) {
  if (node == nullptr)
    return 0;
  return height(node->left) - height(node->right);
}

template <class T>
AVLNode<T> * AVLTree<T>::rightRotate(AVLNode<T> *y) {
  AVLNode<T> *x = y->left;
  AVLNode<T> * T2 = x->right;
  // Realizar la rotacion
  x->right = y;
  y->left = T2;
  // Actualizar alturas
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  // regresar la nueva raiz
  return x;
}

template <class T>
AVLNode<T> * AVLTree<T>::leftRotate(AVLNode<T> *x) {
  AVLNode<T> *y = x->right;
  AVLNode<T> *T2 = y->left;
  // Realizar la rotacion
  y->left = x;
  x->right = T2;
  // Actualizar alturas
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  // regresar la nueva raiz
  return y;
}

template<class T>
AVLNode<T>* AVLTree<T>::insertRecursive(AVLNode<T> *node, T key) {
    // 1. Realizar la insercion normal en un BST
    if (node == nullptr)
      return(new AVLNode<T>(key));
    if (key < node->data)
      node->left = insertRecursive(node->left, key);
    else if (key > node->data)
      node->right = insertRecursive(node->right, key);
    else // Equal keys are not allowed in BST
      return node;

    // 2. Actualizar height de los ancestros del nodo insertado 
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Obtener el factor de balance de su nodo ancestro
    //    para verificar si este se desbalancea
    int balance = getBalance(node);

    // Si se desbalancea, entonces hay 4 casos
    // y es hijo izquierdo de z, además x es hijo izquierdo de y
    // Caso Left Left
    if (balance > 1 && key < node->left->data)
      return rightRotate(node);
    // y es hijo derecho de z, además x es hijo derecho de y
    // Caso Right Right
    if (balance < -1 && key > node->right->data)
      return leftRotate(node);
    // y es hijo izquierdo de z, además x es hijo derecho de y
    // Caso Left Right
    if (balance > 1 && key > node->left->data) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
    // y es hijo derecho de z, además x es hijo izquierdo de y
    // Caso Right Left
    if (balance < -1 && key < node->right->data) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
    // Regresar el apuntador a node (sin cambio)
    return node;
  }

  template<class T>
  void AVLTree<T>::insert(T valor) {
    root = insertRecursive(root, valor);  
  }

  template <class T>
  AVLNode<T>* AVLTree<T>::getSuccessor(AVLNode<T> *p) {
    AVLNode<T> *current = p;
    while (current && current->left != NULL) {
      current = current->left;
    }
    return current;
  }

  template <class T>
  AVLNode<T>* AVLTree<T>::deleteRecursive(AVLNode<T>* root, T value) { 
    // 1. Realiza borrado estandar en BST
    if (root == nullptr)
      return root;
    // Si key < root->data, entonces esta en subarbol izquierdo
    if (value < root->data)
      root->left = deleteRecursive(root->left, value);
    // Si key > root->data, entonces esta en subarbol derecho
    else if(value > root->data)
      root->right = deleteRecursive(root->right, value);
    // Si key == root->data, entonces este es el nodo a borrar
    else { // Hemos localizado el nodo a borrar
      // Node a borrar con un solo hijo o sin hijos
      if((root->left == nullptr) || (root->right == nullptr)) {
        AVLNode<T> *temp = root->left ? root->left : root->right;
        // Nodo a borrar sin hijos
        if (temp == nullptr) {
          temp = root;
          root = nullptr;
        }
        else // Nodo a borrar con un solo hijo 
          *root = *temp; // Copiar el contenido del hijo en root
        delete temp;
      }
      else {
        // Nodo a borrar con dos hijos
        AVLNode<T> *temp = getSuccessor(root->right);
        root->data = temp->data;
        root->right = deleteRecursive(root->right, temp->data);
      }
    }
    // Si el AVL tiene solo un nodo entonces regresalo
    if (root == nullptr)
      return root;
    // 2. Actualizar height del nodo actual 
    root->height = 1 + max(height(root->left), height(root->right));
    // 3. Obtener el factor de balance de este nodo 
    int balance = getBalance(root);
    // Si se desbalancea, entonces hay 4 casos
    // Caso Left Left
    if (balance > 1 && getBalance(root->left) >= 0)
      return rightRotate(root);
    // Caso Left Right
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Caso Right Right
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    // Caso Right Left
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
  }

  template<class T>
  void AVLTree<T>::remove(T valor) {
    root = deleteRecursive(root, valor);  
  }


#endif   // _AVLTREE_H_

