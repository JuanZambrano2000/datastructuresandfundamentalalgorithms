
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
#include "Registro.h"
#include "VectorRegistros.h"
#include "MaxHeap.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>

int main() {
  VectorRegistros bitacora("bitacoraHeap.txt");
  bitacora.heapSort();
  bitacora.imprime("bitacoraResultado.txt");
  bitacora.contarRepeticiones();
  bitacora.reporteIPs("ips_con_mayor_acceso.txt");
  /*
  bitacora.imprime("bitacoraResultado.txt");
  MaxHeap<Registro> bitacoraHeap(bitacora.getSize());
  for(int i=0; i<bitacora.getSize();i++){
    bitacoraHeap.push(bitacora.getData(i));
  }
  std::cout<<bitacoraHeap.getCurrentSize()<<std::endl;
  //std::cout<<bitacoraHeap.<<std::endl;
  bitacoraHeap.print();
  */
  return 0;
}
