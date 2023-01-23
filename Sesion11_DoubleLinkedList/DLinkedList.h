#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include "DLLNode.h"
  
template <class T>
class DLinkedList {
  private:
    DLLNode<T> *head;
    DLLNode<T> *tail;
    int numElements;

  public:
    DLinkedList();
    ~DLinkedList();
    int getNumElements();
    void printList();
    void printListReversed();
    void addFirst(T value);
    void addLast(T value);
    bool deleteData(T value);
    bool deleteAt(int position);
    T getData(int position);

    // To-do
    //void updateData(T value, T newValue);
    //void updateAt(int position, T newValue);
    //int findData(T value);
    //LinkedList(LinkedList<T> lista); 

};

template <class T>
DLinkedList<T>::DLinkedList() {
  std::cout << "---> Creando una lista ligada vacia: " << this << std::endl;
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

template<class T>
DLinkedList<T>::~DLinkedList() {
  std::cout << "---> Liberando memoria de la lista ligada: " << this << std::endl;
  DLLNode<T> *p, *q;
  p = head;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

template <class T> 
int DLinkedList<T>::getNumElements() {
  return numElements;
}

template<class T>
void DLinkedList<T>::printList() {
  DLLNode<T> *ptr = head;
  while (ptr != nullptr) {
      std::cout << ptr->data << " ";
      ptr = ptr->next;
  }
  std::cout << std::endl;
}

template<class T>
void DLinkedList<T>::printListReversed() {
  DLLNode<T> *ptr = tail;
  while (ptr != nullptr) {
      std::cout << ptr->data << " ";
      ptr = ptr->prev;
  }
  std::cout << std::endl;
}

template <class T> 
void DLinkedList<T>::addFirst(T value) {
  // crea un nuevoNodo
  DLLNode<T> *newNode = new DLLNode<T>(value);
  // Si la lista esta vacia
  if (head == nullptr && tail == nullptr) {
    head = newNode;
    tail = newNode;
  }
  else {
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
  }
  numElements++;
}

template <class T> 
void DLinkedList<T>::addLast(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr) {
    addFirst(value);
  }
  else {
    // 1. crea un nuevoNodo
    DLLNode<T> *newNode = new DLLNode<T>(value);
    // 2. apunto tail->next a el nuevoNodo
    tail->next = newNode;
    newNode->prev = tail;
    // 3. Actualizo tail para que apunte al nuevoNodo
    tail = newNode;
    numElements++;
  }
}

template <class T> 
bool DLinkedList<T>::deleteData(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr) {
    return false;
  }
  else {
    DLLNode<T> *p = head;
    DLLNode<T> *previous = nullptr;
    while (p != nullptr && p->data != value) {
      previous = p;
      p = p->next;
    }
    // si no existe value en la lista
    if (p == nullptr)
      return false;
    // si debe borrarse el primer elemento de la lista
    if (p != nullptr && p == head) {
      head = p->next;
      if (head != nullptr)
        head->prev = nullptr;
      if (head == nullptr) // si habia un solo nodo en la lista
        tail = nullptr;
    }
    else if (p->next == nullptr) { // si debe borrarse el ultimo nodo de la lista
      previous->next = nullptr;
      tail = previous;
    }
    else { // si debe borrarse cualquier otro elemento
      previous->next = p->next;
      p->next->prev = previous;
    }
    delete p;
    numElements--;
    return true;
  }
}

template <class T> 
bool DLinkedList<T>::deleteAt(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  }
  else if (position == 0) { // borrar primer nodo de la lista
    DLLNode<T> *p = head;
    // si la lista contiene solo un nodo
    if (head != nullptr && head->next == nullptr)
      head = tail = nullptr;
    else {
      head = p->next;
      head->prev = nullptr;
    }
    delete p;
    numElements--;
    return true;
  }
  else { // borrar cualquier otro nodo de la lista
    DLLNode<T> *p = head;
    DLLNode<T> *previous = nullptr;
    int index = 0;
    // buscar el indice del elemento a borrar
    while (index != position) {
      previous = p;
      p = p->next;
      index++;
    }
    // si debe borrarse el ultimo elemento
    if (p->next == nullptr) {
      previous->next = nullptr;
      tail = previous;
    }
    else { // borrar cualquier otro nodo
      previous->next = p->next;
      p->next->prev = previous;
    }
    delete p;
    numElements--;
    return true;
  }
}

template <class T> 
T DLinkedList<T>::getData(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  }
  else {
    if (position == 0) { // si es el primero de la lista
      return head->data;
    }
    // debemos buscar el elemento
    DLLNode<T> *p = head;
    int index = 0;
    // buscar el indice del elemento a borrar
    while (p != nullptr) {
      if (index == position)
        return p->data;
      p = p->next;
      index++;
    }
    return {};
  }
}


#endif // _DLINKEDLIST_H_
