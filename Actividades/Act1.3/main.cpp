/**
 * Ejemplo que implementa objetos de la clase Registro
 * que contienen una fecha-hora convertida a Linux timestamp
 * para realizar comparaciones (sobrecarga de operadores)
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
 *    ./main > bitacoraOrdenada.txt
 **/
#include "Registro.h"
#include "VectorRegistros.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>

int main() {
  // Sort con ambos algoritmos
  VectorRegistros bitacora1("bitacora.txt");
  VectorRegistros bitacora2("bitacora.txt");
  bitacora1.bubbleSort();
  std::cout << "Reporte Algoritmo bubbleSort: " <<std::endl;
  bitacora1.reporte();
  bitacora2.quickSort(0, bitacora2.getSize());
  std::cout << "Reporte Algoritmo quickSort: " <<std::endl;
  bitacora2.reporte();
  // mandar vector ordenado a archivo .txt
  bitacora2.imprime("bitacora_ordenada.txt");
  std::cout << "---Sección de filtrado del vector: ---" << std::endl;
  std::string mes1, mes2, dia1, dia2, hora1, hora2, minuto1, minuto2, segundo1,
      segundo2, fecha1, fecha2;
  std::cout << "Ingresa mes 1 formato Mmm: " << std::endl;
  std::cin >> mes1;
  std::cout << "Ingresa dia 1 formato DD: " << std::endl;
  std::cin >> dia1;
  std::cout << "Ingresa hora 1 formato hh: " << std::endl;
  std::cin >> hora1;
  std::cout << "Ingresa minuto 1 formato mm: " << std::endl;
  std::cin >> minuto1;
  std::cout << "Ingresa segundo 1 formato ss: " << std::endl;
  std::cin >> segundo1;
  std::cout << "Ingresa mes 2 formato Mmm: " << std::endl;
  std::cin >> mes2;
  std::cout << "Ingresa dia 2 formato DD: " << std::endl;
  std::cin >> dia2;
  std::cout << "Ingresa hora 2 formato hh: " << std::endl;
  std::cin >> hora2;
  std::cout << "Ingresa minuto 2 formato mm: " << std::endl;
  std::cin >> minuto2;
  std::cout << "Ingresa segundo 2 formato ss: " << std::endl;
  std::cin >> segundo2;
  std::cout<<""<<std::endl;
  int numInferior =
      bitacora2.binarySearch(mes1, dia1, hora1, minuto1, segundo1);
  int numSuperior =
      bitacora2.binarySearch(mes2, dia2, hora2, minuto2, segundo2);
  if (numInferior == -1 || numSuperior == -1) {
    std::cout << "Una de las dos fechas no se encuentra en registros ;(";
  } else if (numSuperior < numInferior) {
    std::cout << "Sus fechas están en orden incorrecto >:(";
  } else {
    std::vector<Registro> resp = bitacora2.reducir(numInferior, numSuperior);
    std::cout<<"Resultado: "<<resp.size()<< " registros." << std::endl;
    for (int i = 0; i < resp.size(); i++) {
      std::cout << resp[i].getAll() << std::endl;
    }
  }

  return 0;
}
