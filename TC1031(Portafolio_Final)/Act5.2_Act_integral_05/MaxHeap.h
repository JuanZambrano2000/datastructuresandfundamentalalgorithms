#ifndef _MAXHEAP_H_
#define _MAXHEAP_H_

#include <iostream>
#include <stdexcept>
#include <vector>

template <class T> class MaxHeap {
private:
  // contiene los elementos del heap
  std::vector<T> data;
  // capacidad maxima del heap
  int maxSize;
  // tamano actual del heap
  int currentSize;
  void heapifyD(T value);
  int parent(int k);
  int left(int k);
  int right(int k);
  void heapifyDown(int i);

public:
  MaxHeap();
  MaxHeap(int capacity);
  ~MaxHeap();
  bool isEmpty();
  int getCapacity();
  void setCapacity(int capacity);
  int getCurrentSize();
  void print();
  void push(T key);
  T top();
  // TO-DO
  // T pop();
  void pop();
};

template <class T> MaxHeap<T>::MaxHeap() {
  maxSize = 0;
  currentSize = 0;
}

template <class T> MaxHeap<T>::MaxHeap(int capacity) {
  maxSize = capacity;
  currentSize = 0;
  data.resize(maxSize);
}

template <class T> MaxHeap<T>::~MaxHeap() {
  maxSize = 0;
  currentSize = 0;
  data.clear();
}

template <class T> bool MaxHeap<T>::isEmpty() { return (currentSize <= 0); }

template <class T> int MaxHeap<T>::getCapacity() { return maxSize; }

template <class T> int MaxHeap<T>::getCurrentSize() { return currentSize; }

template <class T> void MaxHeap<T>::print() {
  std::cout << "Contenido del maxheap:" << std::endl;
  for (int i = 0; i < currentSize; i++) {
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}

template <class T> void MaxHeap<T>::setCapacity(int capacity) { maxSize = capacity; currentSize = 0; data.resize(maxSize); }

template <class T> int MaxHeap<T>::parent(int k) { return (k - 1) / 2; }

template <class T> int MaxHeap<T>::left(int k) { return (2 * k + 1); }

template <class T> int MaxHeap<T>::right(int k) { return (2 * k + 2); }

template <class T> void MaxHeap<T>::push(T key) {
  if (currentSize == maxSize) {
    throw std::out_of_range("Overflow: no se puede insertar la llave");
  }
  // Insertamos la nueva llave al final del vecor
  int k = currentSize;
  data[k] = key;
  currentSize++;
  // Reparar las propiedades del maxheap si son violadas
  while (k != 0 && data[parent(k)] < data[k]) {
    std::swap(data[k], data[parent(k)]);
    k = parent(k);
  }
}

//ingresamos el indice que queremos checar que este en orden (el mayor), si el nodo hijo es mayor que uno de los padres son intercambiados, como tenemos que recorrer como maximo el numero de raices la complejidad es de O(logn)
template <class T> void MaxHeap<T>::heapifyDown(int index) {
  int max = index;
  int l = left(index);
  int r = right(index);
  if (l < getCurrentSize() && data[l] > data[max])
    max = l;
  if (r < getCurrentSize() && data[r] > data[max])
    max = r;
  if (max != index) {
    std::swap(data[index], data[max]);
    heapifyDown(max);
  }
}
//Eliminamos la raiz del arbol (el mayor valor), si el arbol esta vacio regresa una excepcion y si tiene un solo elemento lo borra, si tiene mas de uno lo elimina y luego verifica que el arbol siga siendo un heap
template <class T> void MaxHeap<T>::pop() {
  if (isEmpty())
    throw std::out_of_range("No existen elementos en el heap");
  if (getCurrentSize() == 1){
    data.pop_back();
    currentSize--;
  }
  data[0] = data.back();
  data.pop_back();
  heapifyDown(0);
  currentSize--;
}

template <class T> T MaxHeap<T>::top() {
  if (isEmpty()) {
    throw std::out_of_range("El heap esta vacio");
    return {};
  }
  return data[0];
}

#endif // _MAXHEAP_H_