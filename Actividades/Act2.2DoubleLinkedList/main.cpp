/**
 * Ejemplo que implementa una lista ligada con head y tail
 *
 * Compilacion para debug:
 *    g++ -std=c++17 -Wall -g -o main *.cpp
 * Ejecucion con valgrind:
 *    nix-env -iA nixpkgs.valgrind
 *    valgrind --leak-check=full ./main
 *
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -Wall -O3 -o main *.cpp
 * Ejecucion:
 *    ./main
 *
 * Act 2.2 - Implementación de un ADT de Double Linked List 
 * Hecho por los Alumnos:
 * Juan Pablo Zambrano Barajas A01636420
 * Samuel García Berenfeld A01642317
 * TC1031 con el profesor Eduardo Tello
 * Creado el 23/01/2023, ultima modificacion 24/01/2023
 **/


#include <iostream>
#include "DLinkedList.h"


int main() {

  DLinkedList<int> miLista;
  
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  // addFirst
  std::cout << "Agregando 5 elementos al frente..." << std::endl;
  for (int i = 1; i < 6; i++) {
    miLista.addFirst(i);
  }
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  std::cout << "printList: " << std::endl;
  miLista.printList();
  miLista.printListReversed();
  std::cout << std::endl;
  
  // addLast
  std::cout << "Agregando 5 elementos al final..." << std::endl;
  for (int i = 10; i < 15; i++) {
    miLista.addLast(i);
  }
  miLista.addLast(14);
  miLista.addLast(15);
  miLista.addFirst(50);
  miLista.addFirst(45);
  miLista.printList();
  std::cout <<"Lista invertida"<<std::endl;
  miLista.invert();
  miLista.printList();
  miLista.sort();
  std::cout <<"Lista ordenada"<<std::endl;
  miLista.printList();
  DLinkedList<int> miLista2 = miLista.getReversedSublist(2, 5);
  miLista2.printList();
  
  /*
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  std::cout << "printList: " << std::endl;
  miLista.printList();
  miLista.printListReversed();
  std::cout << std::endl;


  // deleteData
  std::cout << "Delete 12: " << std::endl;
  miLista.deleteData(12);
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  miLista.printList();
  std::cout << "Delete 5: " << std::endl;
  miLista.deleteData(5);
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  miLista.printList();
  std::cout << "Delete 14: " << std::endl;
  miLista.deleteData(14);
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  std::cout << "printList: " << std::endl;
  miLista.printList();
  std::cout << "Delete 114: " << std::endl;
  miLista.deleteData(114);
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  std::cout << "printList: " << std::endl;
  miLista.printList();
  miLista.printListReversed();
  std::cout << std::endl;


  // DeleteAt puede lanzar una excepcion
  std::cout << "DeleteAt 2: " << std::endl;
  try {
    miLista.deleteAt(2);
  }
  catch (std::out_of_range &e) {
    std::cout << "Error: " << e.what() << std::endl << "No se modifico la lista" << std::endl;
  }
  catch (...) {
    std::cout << "Error desconocido, no se modifico la lista" << std::endl;
  }
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  miLista.printList();
  std::cout << "DeleteAt 19: " << std::endl;
  try {
    miLista.deleteAt(19);
  }
  catch (std::out_of_range &e) {
    std::cout << "Error: " << e.what() << std::endl << "No se modifico la lista" << std::endl;
  }
  catch (...) {
    std::cout << "Error desconocido, no se modifico la lista" << std::endl;
  }
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  miLista.printList();
  std::cout << std::endl;

  // getData
  try {
    std::cout << "getData(3): " << miLista.getData(3) << std::endl;
  }
  catch (std::out_of_range &e) {
    std::cout << "Error: " << e.what() << std::endl << "No se modifico la lista" << std::endl;
  }
  catch (...) {
    std::cout << "Error desconocido, no se modifico la lista" << std::endl;
  }
    try {
    std::cout << "getData(13): " << miLista.getData(13) << std::endl;
  }
  catch (std::out_of_range &e) {
    std::cout << "Error: " << e.what() << std::endl << "No se modifico la lista" << std::endl;
  }
  catch (...) {
    std::cout << "Error desconocido, no se modifico la lista" << std::endl;
  }

*/
  
  return 0;
}