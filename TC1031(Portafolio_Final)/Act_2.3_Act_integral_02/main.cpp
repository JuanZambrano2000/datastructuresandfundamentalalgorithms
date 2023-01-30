
/**
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
  //DLLRegistro bitacora("bitacora.txt");
  DLLRegistro bitacora("bitacora-1.txt");
  std::cout << bitacora.getSize() << std::endl;
  //bitacora.printToConsole();
  bitacora.mergeSort();
  bitacora.printToTextFile("bitacora_ordenada.txt");

  return 0;
}
