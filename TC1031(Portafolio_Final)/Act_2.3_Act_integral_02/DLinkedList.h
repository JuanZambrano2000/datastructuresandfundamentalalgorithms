#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_

#include "DLLNode.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

class DLinkedList {
private:
  DLLNode *head;
  DLLNode *tail;
  int numElements;
  // quicksort
  void auxQuickSort(DLLNode *l, DLLNode *h);
  DLLNode *partition(DLLNode *l, DLLNode *h);
  // mergeSort
  DLLNode *merge(DLLNode *first, DLLNode *second);
  DLLNode *auxMergeSort(DLLNode *h);
  DLLNode *split(DLLNode *h);

public:
  DLinkedList();
  ~DLinkedList();
  int getNumElements();
  void printList();
  void addFirst(Registro value);
  std::string getData(int position);
  void quickSort();
  void mergeSort();
  DLinkedList getSublist(int start, int end);
};

// Constructor por defecto, una lista enlazada doble sin nodos, tiene un tiempo
// de ejecucion constante (O(1)).
DLinkedList::DLinkedList() {
  // std::cout << "---> Creando una lista ligada vacia: " << this << std::endl;
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}
// Destructor, al terminar el programa se ejecuta para limpiar el heap de
// memoria, tiene un tiempo de ejecucion de O(n).
DLinkedList::~DLinkedList() {
  std::cout << "---> Liberando memoria de la lista ligada: " << this
            << std::endl;
  DLLNode *p, *q;
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
int DLinkedList::getNumElements() { return numElements; }

// Imprime la lista, desde la cabeza hasta la cola, tiempo de ejecucion de O(n).
void DLinkedList::printList() {
  DLLNode *ptr = head;
  while (ptr != nullptr) {
    std::cout << ptr->data.getAll() << " ";
    ptr = ptr->next;
  }
  std::cout << std::endl;
}

// Agrega un nuevo nodo antes de la cabeza y luego se convierte en la nueva
// cabeza, tiempo de ejecucion de O(1).
void DLinkedList::addFirst(Registro value) {
  // crea un nuevoNodo
  DLLNode *newNode = new DLLNode(value);
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

std::string DLinkedList::getData(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else {
    if (position == 0) { // si es el primero de la lista
      return head->data.getAll();
    }
    // debemos buscar el elemento
    DLLNode *p = head;
    int index = 0;
    // buscar el indice del elemento a borrar
    while (p != nullptr) {
      if (index == position)
        return p->data.getAll();
      p = p->next;
      index++;
    }
    return {};
  }
}
// quickSort
void DLinkedList::quickSort() { auxQuickSort(head, tail); }

void DLinkedList::auxQuickSort(DLLNode *l, DLLNode *h) {
  if (h != nullptr && l != h && l != h->next) {
    DLLNode *p = partition(l, h);
    auxQuickSort(l, p->prev);
    auxQuickSort(p->next, h);
  }
}

DLLNode *DLinkedList::partition(DLLNode *l, DLLNode *h) {
  // Establezco pivote como elemento h
  Registro x = h->data;
  // Similar a size-1 en arreglos
  DLLNode *i = l->prev;
  for (DLLNode *j = l; j != h; j = j->next) {
    if (j->data <= x) {
      i = (i == nullptr) ? l : i->next;
      // swap(&(i->data), &(j->data));
      std::swap(i->data, j->data);
    }
  }
  i = (i == nullptr) ? l : i->next;
  // swap(&(i->data), &(h->data));
  std::swap(i->data, h->data);
  return i;
}
// mergeSort
void DLinkedList::mergeSort() { auxMergeSort(head); }

DLLNode *DLinkedList::auxMergeSort(DLLNode *h) {
  if (!h || !h->next)
    return h;
  DLLNode *second = split(head);

  // Recur for left and right halves
  head = auxMergeSort(head);
  second = auxMergeSort(second);

  // Merge the two sorted halves
  return merge(head, second);
}

DLLNode *DLinkedList::merge(DLLNode *first, DLLNode *second) {
  if (!first)
    return second;
  // If second linked list is empty
  if (!second)
    return first;
  // Pick the smaller value
  if (first->data < second->data) {
    first->next = merge(first->next, second);
    first->next->prev = first;
    first->prev = NULL;
    return first;
  } else {
    second->next = merge(first, second->next);
    second->next->prev = second;
    second->prev = NULL;
    return second;
  }
}

DLLNode *DLinkedList::split(DLLNode *head) {
  DLLNode *fast = head, *slow = head;
  while (fast->next && fast->next->next) {
    fast = fast->next->next;
    slow = slow->next;
  }
  DLLNode *temp = slow->next;
  slow->next = NULL;
  return temp;
}

DLinkedList DLinkedList::getSublist(int start, int end) {
  if (head == nullptr && tail == nullptr) {
    throw std::out_of_range("Lista vacia");
  } else if (start < 0 || start > numElements || end < 0 || end > numElements ||
             end < start) {
    throw std::out_of_range("Alguno de los indices es incorrecto");
  } else {
    DLinkedList tmp;
    DLLNode *p = head;
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
    // Por si quieres la sublista del menor al mayor
    // tmp.invert();
    return tmp;
  }
}

#endif // _DLINKEDLIST_H_
