
#ifndef __GRAPH_H_
#define __GRAPH_H_
#include "GradoIP.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "MaxHeap.h"
#include "ipAddress.h"
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

#define INF 0x3f3f3f3f

class Graph {
private:
  int numNodes;
  int numEdges;
  int bootmaster;
  /*
  Tamaño: 13381, Colisiones: 93043
  Tamaño: 18503, Colisiones: 12042
  Tamaño: 22003, Colisiones: 8037
  Tamaño: 27583, Colisiones: 5411
  */
  int maxElementsHT = 22003;
  // Lista de adyacencia (vector de listas de pares (verticeDestino, peso))
  std::vector<LinkedList<std::pair<int, int>>> adjList;
  // map - permite buscar el indice (numero de vertice) que corresponde a una ip
  // La llave es una ip en formato decimal, almacena un objeto ipAddress
  // ver metodo findIpIndex
  std::map<unsigned int, ipAddress> mapIP;
  MaxHeap<GradoIP> heapIP;
  HashTable<unsigned int, ipAddress> hashTable;
  void split(std::string line, std::vector<int> &res);
  int findIpIndex(std::string ipString);
  std::vector<ipAddress> listaIP;

public:
  Graph();
  ~Graph();
  void crearHeap();
  void loadGraph(std::string fileName);
  void printGraph();
  void printIPs();
  MaxHeap<GradoIP> crearGrafo();
  void reporteIPs(std::string reporte, std::string top5);
  void dijkstraAlgorithm(std::string fileName);
  void printHT();
  void loadHashTable();
  void getColisionesHT();
  void getIPSummary(std::string ip);
};

#endif // __GRAPH_H_