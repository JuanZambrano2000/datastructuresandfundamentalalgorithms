#include "Graph.h"


Graph::Graph() {
  numNodes = 0;
  numEdges = 0;
  adjList.clear();
  heapIP.setCapacity(0);
}

Graph::~Graph() {
  numNodes = 0;
  numEdges = 0;
  adjList.clear();
  for(int i=0;i<heapIP.getCurrentSize();i++){
    heapIP.pop();
  }
  heapIP.setCapacity(0);
}

void Graph::split(std::string line, std::vector<int> & res) {
    size_t strPos = line.find(" ");
    size_t lastPos = 0;
    while (strPos != std::string::npos) {
      res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
      lastPos = strPos + 1;
      strPos = line.find(" ", lastPos);
    }
    res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

int Graph::findIpIndex(std::string ipString) {
  ipAddress tmpIp(ipString, 0);
  std::map<unsigned int, ipAddress>::iterator it;
  int ipIndex = -1;
  it = mapIP.find(tmpIp.getIpValue());
  if(it != mapIP.end())
    ipIndex = it->second.getIpIndex();
  return ipIndex;
}


void Graph::loadGraph(std::string fileName) {
  std::string line, ip1, ip2, peso; 
  int i = 0;
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    while(std::getline(file,line)) { 
      if (i == 0) {
        std::vector<int> res;
        split(line, res);
        numNodes = res[0];
        numEdges = res[1];
        // Reservar memoria para los renglones de la lista de adyacencia
        // Nodos son uno basados (renglon 0 no sera usado)
        adjList.resize(numNodes + 1);
        // Declarar una lista ligada vacia de pares (vertice, peso)
        // para cada renglon y se almacena en el vector
        for (int k = 1; k <= numNodes; k++) {
          LinkedList<std::pair<int, int>> tmpList;
          adjList[k] = tmpList;
        }
      }
      else if (i > 0 && i <= numNodes) {
        ipAddress tmpIP(line, i);
        mapIP.insert({tmpIP.getIpValue(), tmpIP});
        //std::cout << tmpIP << std::endl;
      }
      else if (i > numNodes) {
        std::size_t found = line.find(":", 15);
        ip1 = line.substr(15, found-15);
        std::size_t found2 = line.find(" ", found+1);
        std::size_t found3 = line.find(":", found2+1);
        ip2 = line.substr(found2, found3-found2);
        std::size_t found4 = line.find(" ", found3+1);
        std::size_t found5 = line.find(" ", found4+1);
        peso = line.substr(found4, found5-found4);
        // Crear arista ip1 a ip2 con un peso
        ipAddress tmpIP1(ip1, 0);
        //ipAddress tmpIP2(ip2, 0);
        int ip1Index = findIpIndex(ip1); 
        int ip2Index = findIpIndex(ip2);
        if (ip1Index != -1 && ip2Index != -1) {
          adjList[ip1Index].addLast({ip2Index, stoi(peso)});
          mapIP[tmpIP1.getIpValue()].addToOutDegree();
        }
        else {
          throw std::out_of_range("Incorrect IPs in the edge");
          file.close();
        }
      }
      i++;
    }
    file.close();
  }
}

void Graph::printGraph() {
  std::cout << "numNode: " << numNodes << std::endl;
  std::cout << "numEdges: " << numEdges << std::endl;
  std::cout << "Adjacency List" << std::endl;
  for (int nodeU = 1; nodeU <= numNodes; nodeU++) {
    std::cout << "vertex " << nodeU << ": ";
    NodeLinkedList<std::pair<int, int>> *ptr = adjList[nodeU].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      std::cout << "{" << par.first << "," << par.second << "} ";
      ptr = ptr->next;
    }
    std::cout << std::endl;
  }
}

void Graph::printIPs() {
  std::cout << "IPs" << std::endl;
  std::map<unsigned int, ipAddress>::iterator it;
  for (it = mapIP.begin(); it != mapIP.end(); it++) {
    std::cout << it->second << std::endl;
  }
}

void Graph::crearHeap() {
  if(mapIP.size()==0){
    throw std::out_of_range("No hay elementos que almacenar.");
  }
  heapIP.setCapacity((int)mapIP.size());
  std::map<unsigned int, ipAddress>::iterator it;
  for (it = mapIP.begin(); it != mapIP.end(); it++) {
    GradoIP temp(it->second);
    heapIP.push(temp);
  }   
}

void Graph::reporteIPs(std::string reporte, std::string top5) {
  crearHeap();
  int i = 0;
  if (heapIP.isEmpty()) {
    throw std::out_of_range("El max heap se encuentra vacio");
  } else {
    std::ofstream archivoImprime(reporte);
    std::ofstream archivoTop5(top5);
    if (!archivoImprime.good() && !archivoTop5.good()) {
      archivoImprime.close();
      archivoTop5.close();
      std::cout << "Archivos no encontrado" << std::endl;
    } else {
      while (!heapIP.isEmpty()) {
        //if (heapIP.top().getNumVeces() != 0) {
        archivoImprime << heapIP.top();
        if (i < 5) {
          archivoTop5 << heapIP.top();
          i++;
          }
        //}else
        //break;
      heapIP.pop();
      }
    }
    archivoImprime.close();
  }
}