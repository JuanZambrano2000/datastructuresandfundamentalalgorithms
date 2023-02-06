/** 
* Asesoria - Actividad 4.3 (integral de grafos)
*
* Compilacion para debug:  
*    g++ -std=c++17 -Wall -g -o main *.cpp 
*
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main 
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -Wall -O3 -o main *.cpp 
* Ejecucion:
*    ./main 
**/

#include <iostream>
#include "Graph.h"

int main() {
  Graph graph;
  graph.loadGraph("bitacoraGrafos.txt");
  //graph.loadGraph("bitacoraGrafos.txt");
  //graph.printGraph();
  //graph.printIPs();
  graph.crearHeap();
  graph.reporteIPs("grados_ips.txt","mayores_grados_ips.txt");
  graph.crearHeap();
  graph.dijkstraAlgorithm("distancia_bootmaster.txt");

  return 0;
}