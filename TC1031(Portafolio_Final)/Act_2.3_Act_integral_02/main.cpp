
/*
 * Actividad 1.3, Actividad Integral de Conceptos Básicos y Algoritmos
 *Fundamentales Hecho por los Alumnos: Juan Pablo Zambrano Barajas A01636420
 * Samuel García Berenfeld A01642317
 * TC1031 con el profesor Eduardo Tello
 * Creado el 17/01/2023, ultima modificacion 26/01/2023
 * Compilacion para debug:
 *    g++ -std=c++17 -g -o main *.cpp
 * Ejecucion con valgrind:
 *    nix-env -iA nixpkgs.valgrind
 *    valgrind --leak-check=full ./main
 *
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -Wall -O3 -o main *.cpp
 * Ejecucion:
 *    ./main > bitacoraOrdenada.txt
 **/
#include "DLLRegistro.h"
#include "Registro.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>

int main() {
  // DLLRegistro bitacora("bitacora.txt");
  DLLRegistro bitacora1("bitacora-1.txt");
  DLLRegistro bitacora2("bitacora-1.txt");
  std::cout << bitacora1.getSize() << std::endl;
  // bitacora.printToConsole();
  bitacora1.mergeSort();
  std::cout << "Comparaciones Durante el Megresort: " <<bitacora1.getComparaciones() << std::endl;
  bitacora2.quickSort();
  std::cout << "Comparaciones Durante el quickSort: " <<bitacora2.getComparaciones() << std::endl;
  bitacora1.printToTextFile("bitacora_ordenada.txt");
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
  
  Registro registroA(mes1, dia1, hora1, minuto1, segundo1);

  Registro registroB(mes2, dia2, hora2, minuto2, segundo2);

  bitacora1.binarySearch(registroA);
  int pos1 = bitacora1.getPosicionElemento();
  std::cout << pos1 << std::endl;
  bitacora1.resetPosicionElemento();
  bitacora1.binarySearch(registroB);
  int pos2 = bitacora1.getPosicionElemento();
  std::cout << pos2 << std::endl;
  bitacora1.resetPosicionElemento();
  bitacora1.printSubListToTextFile("resultado_busqueda.txt", pos1, pos2);
  
  return 0;
  //DLLRegistro bitacora3 = bitacora1.getSublist(pos1, pos2);
}

/*
fecha 1: Jun 01 00:22:36
fecha 2: Jun 01 08:23:57
fecha 1: Oct 26 13:37:41
fecha 2: Oct 30 23:48:41
fecha 1: Oct 20 23:45:19
fecha 2: Oct 21 00:29:14
*/