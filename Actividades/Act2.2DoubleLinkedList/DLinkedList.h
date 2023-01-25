#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_

#include "DLLNode.h"
#include <iostream>
#include <stdexcept>

template <class T> class DLinkedList {
private:
  DLLNode<T> *head;
  DLLNode<T> *tail;
  int numElements;
  void swap(T *a, T *b);
  DLLNode<T> *partition(DLLNode<T> *l, DLLNode<T> *h);
  void _sort(DLLNode<T> *l, DLLNode<T> *h);

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
  void updateData(T value, T newValue);
  void updateAt(int position, T newValue);
  int findData(T value);
  void invert();
  void sort();
  DLinkedList<T> getReversedSublist(int start, int end);
};

// Constructor por defecto, una lista enlazada doble sin nodos, tiene un tiempo
// de ejecucion constante (O(1)).
template <class T> DLinkedList<T>::DLinkedList() {
  // std::cout << "---> Creando una lista ligada vacia: " << this << std::endl;
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

// Destructor, al terminar el programa se ejecuta para limpiar el heap de
// memoria, tiene un tiempo de ejecucion de O(n).
template <class T> DLinkedList<T>::~DLinkedList() {
  std::cout << "---> Liberando memoria de la lista ligada: " << this
            << std::endl;
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

// Regresa el numero de elementos, complejidad de O(1).
template <class T> int DLinkedList<T>::getNumElements() { return numElements; }

// Imprime la lista, desde la cabeza hasta la cola, tiempo de ejecucion de O(n).
template <class T> void DLinkedList<T>::printList() {
  DLLNode<T> *ptr = head;
  while (ptr != nullptr) {
    std::cout << ptr->data << " ";
    ptr = ptr->next;
  }
  std::cout << std::endl;
}

// Imprime la lista desde la cola hasta la cabeza, tiene un tiempo de ejecucion
// de O(n).
template <class T> void DLinkedList<T>::printListReversed() {
  DLLNode<T> *ptr = tail;
  while (ptr != nullptr) {
    std::cout << ptr->data << " ";
    ptr = ptr->prev;
  }
  std::cout << std::endl;
}

// Agrega un nuevo nodo antes de la cabeza y luego se convierte en la nueva
// cabeza, tiempo de ejecucion de O(1).
template <class T> void DLinkedList<T>::addFirst(T value) {
  // crea un nuevoNodo
  DLLNode<T> *newNode = new DLLNode<T>(value);
  // Si la lista esta vacia
  if (head == nullptr && tail == nullptr) {
    head = newNode;
    tail = newNode;
  } else {
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
  }
  numElements++;
}

// Agrega un nuevo nodo despues de la cola y luego se convierte en la nueva
// cola, tiempo de ejecucion de O(1).
template <class T> void DLinkedList<T>::addLast(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr) {
    addFirst(value);
  } else {
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

// Elimina un valor de la lista, tiempo de ejecucion en el mejor caso de O(1) y
// en el promedio y peor caso O(n)
template <class T> bool DLinkedList<T>::deleteData(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr) {
    return false;
  } else {
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
    } else if (p->next ==
               nullptr) { // si debe borrarse el ultimo nodo de la lista
      previous->next = nullptr;
      tail = previous;
    } else { // si debe borrarse cualquier otro elemento
      previous->next = p->next;
      p->next->prev = previous;
    }
    delete p;
    numElements--;
    return true;
  }
}

// Dado un indice, esta funcion los busca y borra, tiempo de ejecucion en el
// mejor paso de O(1) y un caso promedio de O(n)
template <class T> bool DLinkedList<T>::deleteAt(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else if (position == 0) { // borrar primer nodo de la lista
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
  } else { // borrar cualquier otro nodo de la lista
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
    } else { // borrar cualquier otro nodo
      previous->next = p->next;
      p->next->prev = previous;
    }
    delete p;
    numElements--;
    return true;
  }
}

// Recorremos el
template <class T> T DLinkedList<T>::getData(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else {
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

// Pasamos el valor que queremos cambiar y el nuevo, recorremos la lista hasta
// encontrarlo y lo cambiamos, tiene una complejidad en el mejor caso de O(1) y
// en el peor y caso promedio de O(n)
template <class T> void DLinkedList<T>::updateData(T value, T newValue) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr) {
    throw std::out_of_range("La lista esta vacia");
  } else {
    DLinkedList<T> *p = head;
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
template <class T> void DLinkedList<T>::updateAt(int position, T newValue) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else {
    DLinkedList<T> *p = head;
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
template <class T> int DLinkedList<T>::findData(T value) {
  int i = 0;
  if (head == nullptr && tail == nullptr) {
    throw std::out_of_range("La lista esta vacia");
  } else {
    DLinkedList<T> *p = head;
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

// Complejidad en tiempo: O(n) donde n es el número de elementos en la lista
template <class T> void DLinkedList<T>::invert() {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr) {
    throw std::out_of_range("Lista vacia");
  } else {
    // 1. crea un nuevo nodo y lo hace null, inicializa otro en la cabeza de la
    // lista
    DLLNode<T> *tmp = nullptr;
    DLLNode<T> *current = head;
    DLLNode<T> *t = head;
    // Invierte los nodos previos y next para cada elemento con ayuda del nodo
    // temporal
    while (current != nullptr) {
      tmp = current->prev;
      current->prev = current->next;
      current->next = tmp;
      current = current->prev;
    }
    if (tmp != nullptr) {
      head = tmp->prev;
      tail = t;
    }
  }
}

//Realiza un swap (igual que el presente en la libreria std pero capaz de hacerlo con apuntadores)
template <class T> void DLinkedList<T>::swap(T *a, T *b) {
  T t = *a;
  *a = *b;
  *b = t;
}

//Codigo para realizar el quick sort, nos apoyamos con la pagina web https://www.geeksforgeeks.org/quick-sort/ 
//Mantenemos los elementos mas pequenos a la izquierda, este algoritmo tiene un tiempo de ejecucion promedio y en el mejor caso de O(nlogn) y en el peor caso de O(n^2) cuando el pivote siempre es el elemento mas grande
template <class T>
DLLNode<T> *DLinkedList<T>::partition(DLLNode<T> *l, DLLNode<T> *h) {
  // Establezco pivote como elemento h
  T x = h->data;
  // Similar a size-1 en arreglos
  DLLNode<T> *i = l->prev;
  for (DLLNode<T> *j = l; j != h; j = j->next) {
    if (j->data <= x) {
      i = (i == nullptr) ? l : i->next;
      swap(&(i->data), &(j->data));
    }
  }
  i = (i == nullptr) ? l : i->next;
  swap(&(i->data), &(h->data));
  return i;
}

//Llama recursivamente a la funcion partition 
template <class T> void DLinkedList<T>::_sort(DLLNode<T> *l, DLLNode<T> *h) {
  if (h != nullptr && l != h && l != h->next) {
    DLLNode<T> *p = partition(l, h);
    _sort(l, p->prev);
    _sort(p->next, h);
  }
}

//Metodo usado para que el usuario pueda llamar a la funcion sin ser abrumado por los todos los atributos que este requiere, tiempo de ejecucion de O(1).
template <class T> void DLinkedList<T>::sort() { _sort(head, tail); }

template <class T>
DLinkedList<T> DLinkedList<T>::getReversedSublist(int start, int end) {
  if (head == nullptr && tail == nullptr) {
    throw std::out_of_range("Lista vacia");
  } else if (start < 0 || start > numElements || end < 0 || end > numElements ||
             end < start) {
    throw std::out_of_range("Alguno de los indices es incorrecto");
  } else {
    DLinkedList<T> tmp;
    DLLNode<T> *p = head;
    int index = 0;
    while (index < start) {
      p = p->next;
      index++;
    }
    while (index <= end) {
      tmp.addFirst(p->data);
      p = p->next;
      index++;
    }
    // tmp.invert();
    return tmp;
  }
}

#endif // _DLINKEDLIST_H_
