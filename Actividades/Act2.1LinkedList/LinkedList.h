#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "NodeLinkedList.h"
#include <iostream>
#include <stdexcept>

template <class T> class LinkedList {
private:
  NodeLinkedList<T> *head;
  NodeLinkedList<T> *tail;
  int numElements;

public:
  LinkedList();
  ~LinkedList();
  int getNumElements();
  void printList();
  void addFirst(T value);
  void addLast(T value);
  bool deleteData(T value);
  bool deleteAt(int position);
  T getData(int position);
  // To-do
  void updateData(T value, T newValue);
  void updateAt(int position, T newValue);
  int findData(T value);
  LinkedList(LinkedList<T> &lista);
};

// Constructor de uns lista enlazada vacia
template <class T> LinkedList<T>::LinkedList() {
  std::cout << "---> Creando una lista ligada vacia: " << this << std::endl;
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}
// Destructor recorre cada elemento de la lista y lo va eliminando para liberal
// la memoria del heap, complejidad de O(n)
template <class T> LinkedList<T>::~LinkedList() {
  std::cout << "---> Liberando memoria de la lista ligada: " << this
            << std::endl;
  NodeLinkedList<T> *p, *q;
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

// Regresa el atributo que corresponde a la cantidad de elementos, complejidad
// O(1)
template <class T> int LinkedList<T>::getNumElements() { return numElements; }

// Imprime cada uno de los elementos de la lista, complejidad O(n)
template <class T> void LinkedList<T>::printList() {
  NodeLinkedList<T> *ptr = head;
  while (ptr != nullptr) {
    std::cout << ptr->data << " ";
    ptr = ptr->next;
  }
  std::cout << std::endl;
}

// Se crea un nuevo nodo que estara apuntando a la cabeza, para despues
// actualizar el apuntador de la cabeza a este, con complejidad de O(1)
template <class T> void LinkedList<T>::addFirst(T value) {
  // 1. crea un nuevoNodo
  NodeLinkedList<T> *newNode = new NodeLinkedList<T>(value);
  // 2. apunto nuevoNodo->next a donde esta head
  newNode->next = head;
  // 3. Actualizo head para que apunte al nuevoNodo
  head = newNode;
  if (numElements == 0)
    tail = newNode;
  numElements++;
}

// Creamos un nodo en la cola y lo hacemos la nueva cola, tiene una complejidad
// de O(1)
template <class T> void LinkedList<T>::addLast(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr) {
    addFirst(value);
  } else {
    // 1. crea un nuevoNodo
    NodeLinkedList<T> *newNode = new NodeLinkedList<T>(value);
    // 2. apunto tail->next a el nuevoNodo
    tail->next = newNode;
    // 3. Actualizo tail para que apunte al nuevoNodo
    tail = newNode;
    numElements++;
  }
}

// Eliminamos un valor de la lista, tiene una complejidad en el mejor caso de
// O(1) y en el peor y caso promedio de O(n)
template <class T> bool LinkedList<T>::deleteData(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr) {
    return false;
  } else {
    NodeLinkedList<T> *p = head;
    NodeLinkedList<T> *prev = nullptr;
    while (p != nullptr && p->data != value) {
      prev = p;
      p = p->next;
    }
    // si no existe value en la lista
    if (p == nullptr)
      return false;
    // si debe borrarse el primer elemento de la lista
    if (p != nullptr && p == head) {
      head = p->next;
      if (head == nullptr) // si habia un solo nodo en la lista
        tail = nullptr;
    } else if (p->next ==
               nullptr) { // si debe borrarse el ultimo nodo de la lista
      prev->next = nullptr;
      tail = prev;
    } else { // si debe borrarse cualquier otro elemento
      prev->next = p->next;
    }
    delete p;
    numElements--;
    return true;
  }
}

// Pasamos un indice, lo iremos recorriendo y al llegar ahi lo borramos,
// cambiando los apuntadores para no perder datos, tiene un complejidad en el
// mejor caso de O(1) y en el peor y caso promedio de O(n)
template <class T> bool LinkedList<T>::deleteAt(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else if (position == 0) { // borrar primer nodo de la lista
    NodeLinkedList<T> *p = head;
    // si la lista contiene solo un nodo
    if (head != nullptr && head->next == nullptr)
      head = tail = nullptr;
    else
      head = p->next;
    delete p;
    numElements--;
    return true;
  } else { // borrar cualquier otro nodo de la lista
    NodeLinkedList<T> *p = head;
    NodeLinkedList<T> *prev = nullptr;
    int index = 0;
    // buscar el indice del elemento a borrar
    while (index != position) {
      prev = p;
      p = p->next;
      index++;
    }
    // si debe borrarse el ultimo elemento
    if (p->next == nullptr) {
      prev->next = nullptr;
      tail = prev;
    } else { // borrar cualquier otro nodo
      prev->next = p->next;
    }
    delete p;
    numElements--;
    return true;
  }
}

// Nos regresa la data segun un indice que el usuario nos indique, tiene una
// complejidad en el mejor caso de O(1) y en el peor y caso promedio de O(n)
template <class T> T LinkedList<T>::getData(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else {
    if (position == 0) { // si es el primero de la lista
      return head->data;
    }
    // debemos buscar el elemento
    NodeLinkedList<T> *p = head;
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

// Pasamos el valor que queremos cambiar y el nuevo, recorremos la lista hasta
// encontrarlo y lo cambiamos, tiene una complejidad en el mejor caso de O(1) y
// en el peor y caso promedio de O(n)
template <class T> void LinkedList<T>::updateData(T value, T newValue) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr) {
    throw std::out_of_range("La lista esta vacia");
  } else {
    NodeLinkedList<T> *p = head;
    // NodeLinkedList<T> *prev = nullptr;
    while (p != nullptr && p->data != value) {
      // prev = p;
      p = p->next;
    }
    // si no existe value en la lista
    if (p == nullptr)
      throw std::out_of_range("El valor no se ha encontrado");
    else
      p->data = newValue;
  }
};

// Recibimos una posicion y el valor que queremos cambiar, tiene una complejidad
// en el mejor caso de O(1) y en el peor y caso promedio de O(n)
template <class T> void LinkedList<T>::updateAt(int position, T newValue) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else {
    NodeLinkedList<T> *p = head;
    if (position == 0) // si es el primero de la lista
      p->data = newValue;
    else {
      // debemos buscar el elemento
      int index = 0;
      // buscar el indice del elemento a cambiar
      while (index < position) {
        p = p->next;
        index++;
      }
      p->data = newValue;
    }
  }
}

// Recibimos un valor y si lo encontramos regresamos el indice donde esta
// guardada, tiene una complejidad en el mejor caso de O(1) y en el peor y caso
// promedio de O(n)
template <class T> int LinkedList<T>::findData(T value) {
  int i = 0;
  if (head == nullptr && tail == nullptr) {
    throw std::out_of_range("La lista esta vacia");
  } else {
    NodeLinkedList<T> *p = head;
    // NodeLinkedList<T> *prev = nullptr;
    while (p != nullptr && p->data != value) {
      // prev = p;
      p = p->next;
      i++;
    }
    // si no existe value en la lista
    if (p == nullptr)
      throw std::out_of_range("El valor no se ha encontrado");
    else
      return i;
  }
}

// Complejidad O(n)
template <class T> LinkedList<T>::LinkedList(LinkedList<T> &lista) {
  if (lista.head == nullptr && lista.tail == nullptr)
    throw std::out_of_range("La lista esta vacia");
  // Crear un nodo temporal
  NodeLinkedList<T> *p = lista.head;
  NodeLinkedList<T> *temp = lista.head;

  // Copiar el valor
  head->data = temp->data;
  // poner el siguiente nodo en null para el while
  head->next = nullptr;
  // Move to next item in ll's list.
  temp = temp->next;

  while (temp != nullptr) {
    // Allocate new memory for a new 'node'.
    p->next = new NodeLinkedList<T>;
    // Point to this new 'node'.
    p = p->next;
    // Copy over the data.
    p->data = temp->data;
    // By default set the 'next' to null.
    p->next = nullptr;
    // Move along ll's list.
    temp = temp->next;
  }
};
#endif // _LINKEDLIST_H_
