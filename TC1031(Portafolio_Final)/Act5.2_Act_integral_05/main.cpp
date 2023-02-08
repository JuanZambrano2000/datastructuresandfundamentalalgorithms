/**
 * Asesoria - Actividad 5.2 (integral de grafos)
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

#include "Graph.h"
#include <iostream>

int main() {
  try {
    //"60.202.46.50"
    std::string ip;
    Graph graph;
    graph.loadGraph("bitacoraGrafos.txt");
    // graph.loadGraph("bitacoraGrafos.txt");
    // graph.printGraph();
    // graph.printIPs();
    graph.loadHashTable();
    graph.getColisionesHT();
    graph.printHT();
    std::cout << "Ingresa una ip: " << std::endl;
    std::cin >> ip;
    try {
      graph.getIPSummary(ip);
    } catch (std::exception &e) {
      std::cout << "Número en formato inválido: " << e.what() << std::endl;
    }
  } catch (std::exception &e) {
    std::cout << "Excepcion: " << e.what() << std::endl;
  }
  return 0;
}