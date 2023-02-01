/**
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
 * Act 3.2 - Implementando una fila priorizada 
 * Hecho por los Alumnos:
 * Juan Pablo Zambrano Barajas A01636420
 * Samuel García Berenfeld A01642317
 * TC1031 con el profesor Eduardo Tello
 * Creado el 26/01/2023, ultima modificacion 26/01/2023
 **/


#include <iostream>
#include "MaxHeap.h"

int main() {
  std::cout << "Prueba de un MaxHeap!\n";
  MaxHeap<int> myMaxHeap(100);
  std::cout << "isEmpty() " << std::boolalpha << myMaxHeap.isEmpty() << std::endl;
  std::cout << "getCapacity() " << myMaxHeap.getCapacity() << std::endl;
  std::cout << "push() de 7 valores" << std::endl;
  myMaxHeap.push(2);
  myMaxHeap.push(3);  
  myMaxHeap.push(1);
  myMaxHeap.push(15);
  myMaxHeap.push(5);
  myMaxHeap.push(4);
  myMaxHeap.push(45);
  myMaxHeap.push(65);
  //myMaxHeap.push(0);
  myMaxHeap.push(22);
  myMaxHeap.push(33);
  //myMaxHeap.push(415);
  /* Max Heap creado 
             45
            /  \
           5    15
          / \   / \
         2   3 1   4
  */
  
  myMaxHeap.print();
  std::cout <<"top(): " << myMaxHeap.top() << std::endl;
  myMaxHeap.pop();
  myMaxHeap.print();
  std::cout <<std::endl;
  return 0;
}