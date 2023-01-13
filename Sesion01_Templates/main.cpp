/*
  compilar:
    g++ -std=c++17 -Wall *.cpp

  ejecutar:
    ./a.out
*/

#include "ListaTemplate.h"
#include <iostream>

int main() {
  std::cout << "Template example!\n";

  ListaTemplate<int> listaInt; // lista de ints

  // agregar valores a la lista
  for (int i = 1; i <= 6; i++)
    if (!listaInt.insert(i * 10))
      std::cout << "no se pudo insertar el elemento en: " << i << std::endl;
  // imprime la lista
  listaInt.print();

  //Obtener un dato
  std::cout << "El dato de la casilla 4 es: " << listaInt.getData(4) << std::endl;
  // obtener tamaño
  std::cout << "Tamaño de la lista: " << listaInt.getSize() << std::endl;

  // borrar último elemento
  std::cout << "El ultimo elemento es: " << std::endl;
  listaInt.erase();

  // obtener tamaño
  std::cout << "Tamaño de la lista: " << listaInt.getSize() << std::endl;

  return 0;
}