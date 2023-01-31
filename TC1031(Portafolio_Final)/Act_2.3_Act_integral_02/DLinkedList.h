#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_

#include "DLLNode.h"
#include "DLLRegistro.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

class DLinkedList {
private:
  //DLLNode *head;
  DLLNode *head;
  DLLNode *tail;
  int numElements;
  int lowElemento;
  int HighElemento;
  int posicionElemento;
  // quicksort
  void auxQuickSort(DLLNode *l, DLLNode *h);
  DLLNode *partition(DLLNode *l, DLLNode *h);
  // mergeSort
  DLLNode *merge(DLLNode *first, DLLNode *second);
  DLLNode *_mergeSort(DLLNode *head);
  DLLNode *split(DLLNode *head);
  // Binary search
  DLLNode *middle(DLLNode *start, DLLNode *last);
  DLLNode *auxBinarySearch(DLLNode *h, Registro value);
  int comparaciones = 0;

public:
  DLinkedList();
  ~DLinkedList();
  int getNumElements();
  void printList();
  void addFirst(Registro value);
  void addLast(Registro value);
  //std::string getData(int position);
  void quickSort();
  void mergeSort();
  void binarySearch(Registro value);
  int getPosicionElemento();
  void resetPosicionElemento();
  DLLNode *getHead();
  std::string getData(DLLNode *ptr);
  int getComparaciones();
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

// Agrega un nuevo nodo despues de la cola y luego se convierte en la nueva
// cola, tiempo de ejecucion de O(1).
void DLinkedList::addLast(Registro value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr) {
    addFirst(value);
  } else {
    // 1. crea un nuevoNodo
    DLLNode *newNode = new DLLNode(value);
    // 2. apunto tail->next a el nuevoNodo
    tail->next = newNode;
    newNode->prev = tail;
    // 3. Actualizo tail para que apunte al nuevoNodo
    tail = newNode;
    numElements++;
  }
}

// quickSort, tiene una complejidad de O(n^2) en el peor caso que es cuando la lista ya esta ordenada y un caso promedio y mejor caso O(nLogn), para ejecutarse necesita de O(n) espacio
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
    comparaciones++;
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

// Función que llamará a los diferentes métodos del mergeSort
//La complejidad en tiempo es = O(n log n).
//Por lo mismo es más eficiente mientras incrementan los datos, ya que se hacen más llamadas cada poder.
void DLinkedList::mergeSort() { head = _mergeSort(head); }

DLLNode * DLinkedList::split(DLLNode *head) { 
    DLLNode *fast = head, *slow = head; 
    while (fast->next && fast->next->next) { 
        fast = fast->next->next; 
        slow = slow->next; 
    } 
    DLLNode *temp = slow->next; 
    slow->next = nullptr; 
    return temp; 
} 

DLLNode * DLinkedList::merge(DLLNode *first, DLLNode *second) { 
    // Si la primera lista está vacía
    if (!first) 
        return second; 
    // Si la segunda lista está vacía
    if (!second) 
        return first; 
    // Se hace la comparacion de los datos y se registra una comparación. 
    comparaciones ++;
    if (first->data < second->data) { 
      //Si el primer dato es menor se pega la primera al principio y la segunda al final
      first->next = merge(first->next, second); 
      first->next->prev = first; 
      first->prev = nullptr; 
      return first; 
    } 
    else { 
      //Lo opuesto ocurre si el segundo dato es el mayor.
      second->next = merge(first, second->next); 
      second->next->prev = second; 
      second->prev = nullptr; 
      return second; 
    } 
} 

DLLNode * DLinkedList::_mergeSort(DLLNode *head) { 
    if (!head || !head->next) 
        return head; 
    DLLNode *second = split(head); 
  
    // Recurrir para la mitad izquierda y derecha 
    head = _mergeSort(head); 
    second = _mergeSort(second); 
  
    // Pegar las dos mitades 
    return merge(head, second); 
}

// El binarySearch tiene una complejidad O(logN) y requiere de un espacio auxiliar de O(N), tiene la desventaja frente al sequential search de que el arreglo tiene que estar ordenado, divide la mitad y descarta la mitad dependiendo si el valor a buscar es mas pequeno o mas grande y asi hasta encontrar el valor.
void DLinkedList::binarySearch(Registro value) { auxBinarySearch(head, value); }

DLLNode *DLinkedList::auxBinarySearch(DLLNode *h, Registro value) {
  DLLNode *start = h;
  DLLNode *last = NULL;
  lowElemento = 0;
  HighElemento = numElements;
  posicionElemento = 0;
  do {
    posicionElemento = (lowElemento + HighElemento) / 2;
    // Find middle
    DLLNode *mid = middle(start, last);
    // If middle is empty
    if (mid == NULL)
      return NULL;
    // If value is present at middle
    if (mid->data == value) {
      std::cout << "valor encontrado" << std::endl;

      return mid;
    } else if (mid->data < value) { // If value is more than mid
      // HighElemento = posicionElemento - 1;
      lowElemento = posicionElemento + 1;
      start = mid->next;
      posicionElemento = posicionElemento / 2;
      // If the value is less than mid.
    } else {
      // lowElemento = posicionElemento + 1;
      HighElemento = posicionElemento - 1;
      last = mid;
      posicionElemento = posicionElemento / 2;
    }
  } while (last == NULL || last != start);
  // value not present
  posicionElemento = -1;
  std::cout << "El valor no esta en la lista" << std::endl;
  return NULL;
}

DLLNode *DLinkedList::middle(DLLNode *start, DLLNode *last) {
  if (start == NULL)
    return NULL;
  DLLNode *slow = start;
  DLLNode *fast = start->next;

  while (fast != last) {
    fast = fast->next;
    if (fast != last) {
      slow = slow->next;
      fast = fast->next;
    }
  }
  return slow;
}

int DLinkedList::getPosicionElemento() { return posicionElemento; }

void DLinkedList::resetPosicionElemento() {
  posicionElemento = 0;
  lowElemento = 0;
  HighElemento = 0;
};

DLLNode *DLinkedList::getHead(){ return head; }

std::string DLinkedList::getData(DLLNode *ptr) {
  return ptr->data.getAll();
}

int DLinkedList::getComparaciones(){
  return comparaciones;
}
#endif // _DLINKEDLIST_H_
