#ifndef _LISTA_H_
#define _LISTA_H_

#include <iostream>
#include <vector>

const int MAX = 100;

template <class T>
class ListaTemplate {
  private:
    std::vector<T> data;
    // tamaño actual de la lista
    int currentSize; 

  public:
    ListaTemplate();
    ~ListaTemplate();
    bool insert(T value);
    void erase();
    T getData(int indice);
    int getSize();
    void print();
};


template <class T>
ListaTemplate<T>::ListaTemplate() {
  std::cout << "Constructor" << std::endl;
  currentSize = 0;
  data.clear();
}

template <class T>
ListaTemplate<T>::~ListaTemplate() {
  std::cout << "Destructor" << std::endl;
  currentSize = 0;
  data.clear();
}

template <class T>
bool ListaTemplate<T>::insert(T value) {
  if (currentSize < MAX) {
    data.push_back(value);
    currentSize++;
    std::cout << "Elemento insertado" << std::endl;
    return true;
  }
  else
    return false;
}

template<class T>
void ListaTemplate<T>::erase() {
  if (currentSize > 0) {
    std::cout << getData(currentSize-1) << std::endl;
    data.pop_back();
    currentSize--;
  }
  else
    std::cout << "NO HAY ELEMENTOS" << std::endl;
}

template<class T>
T ListaTemplate<T>::getData(int indice) {
  return data[indice];
}

template<class T>
void ListaTemplate<T>::print() {
  std::cout << "Contenido de la lista" << std::endl;
  for (int i = 0; i < currentSize; i++) {
    std::cout << "["<< i << "] -- "<< data[i] << std::endl;
  }
}

template<class T>
int ListaTemplate<T>::getSize() {
  return currentSize;
}

#endif  // _LISTA_H_

