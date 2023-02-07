/**
* Tabla Hash que utiliza el método Encadenamiento Externo (Hashing Abierto)
*
* Compilacion para debug:
*    g++ -std=c++17 -g -o main *.cpp
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main
*
* Compilacion para ejecucion:
*    g++ -std=c++17 -O3 -o main *.cpp
* Ejecucion:
*    ./main
**/

#include <iostream>
#include <string>
#include "OAHashTable.h"

int main() {
  OAHashTable<std::string> myOAHT(7);
  //myOAHT.setMaxSize(7);
  myOAHT.add(5, "Hola");
  myOAHT.add(6, "Mundo");
  myOAHT.add(15, "Cruel");
  myOAHT.add(7, "Saludos");
  myOAHT.add(13, "De Diversión");
  myOAHT.add(69, "Achu");

  std::cout<<"Resultado de la busqueda (valor extraño): "<< myOAHT.find(33)<<std::endl;
  std::cout<<"Resultado de la busqueda (valor en table): "<< myOAHT.find(13)<<std::endl<<std::endl;
  std::cout<<"Imprimir lista: "<<std::endl;
  myOAHT.print();
  std::cout<<""<<std::endl;
  std::cout << "Elmininamos un dato (llave = 6)" << std::endl<<std::endl;
  myOAHT.remove(6);
  std::cout << "Imprimimos lista sin dato eliminado:  " << std::endl;
  myOAHT.print();


  return 0;
}