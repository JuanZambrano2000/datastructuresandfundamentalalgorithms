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
 * Act 3.1 - Operaciones avanzadas en un BST  
 * Hecho por los Alumnos:
 * Juan Pablo Zambrano Barajas A01636420
 * Samuel García Berenfeld A01642317
 * TC1031 con el profesor Eduardo Tello
 * Creado el 24/01/2023, ultima modificacion 26/01/2023
 **/


#include "BST.h"
#include <iostream>

int main() {
  std::cout << "Ejemplo de un Binary Search Tree (BST)\n";

  BST<int> myBST;
  myBST.insert(10);
  myBST.insert(20);
  myBST.insert(30);
  myBST.insert(15);
  myBST.insert(5);
  myBST.insert(115);
  myBST.insert(3);
  myBST.insert(3);

  /*
                    10
            5               20
        3             15          30
                                      115
  */
  myBST.print();
  myBST.ancestors(30);
  std::cout<<"Nivel 30: "<< myBST.whatlevelamI(30) <<std::endl;
  std::cout<<"Nivel 115: "<< myBST.whatlevelamI(115) <<std::endl;
  std::cout<<"Nivel 1115: "<< myBST.whatlevelamI(1115) <<std::endl;
  std::cout<<"Nivel 10: "<< myBST.whatlevelamI(10) <<std::endl;

  return 0;
}