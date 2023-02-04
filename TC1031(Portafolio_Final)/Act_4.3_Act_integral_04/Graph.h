
#ifndef __GRAPH_H_
#define __GRAPH_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "LinkedList.h"
#include "ipAddress.h"
#include "MaxHeap.h"
#include "GradoIP.h"


class Graph {
  private:
    int numNodes;
    int numEdges;
    // Lista de adyacencia (vector de listas de pares (verticeDestino, peso))
    std::vector<LinkedList<std::pair<int,int>>> adjList;
    // map - permite buscar el indice (numero de vertice) que corresponde a una ip
    // La llave es una ip en formato decimal, almacena un objeto ipAddress
    // ver metodo findIpIndex
    std::map<unsigned int, ipAddress> mapIP;
    MaxHeap<GradoIP> heapIP;
    void split(std::string line, std::vector<int> & res);
    int findIpIndex(std::string ipString);
    void crearHeap();
  public:
    Graph();
    ~Graph();
    void loadGraph(std::string fileName);
    void printGraph();
    void printIPs();
    MaxHeap<GradoIP> crearGrafo();
    void reporteIPs(std::string reporte, std::string top5);
    

};




#endif // __GRAPH_H_