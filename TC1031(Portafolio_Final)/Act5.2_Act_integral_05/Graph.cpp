#include "Graph.h"

// Constructor por defecto
Graph::Graph() {
  numNodes = 0;
  numEdges = 0;
  adjList.clear();
  heapIP.setCapacity(0);
  listaIP.clear();
}

// Destructor
Graph::~Graph() {
  numNodes = 0;
  numEdges = 0;
  adjList.clear();
  for (int i = 0; i < heapIP.getCurrentSize(); i++) {
    heapIP.pop();
  }
  heapIP.setCapacity(0);
  listaIP.clear();
}

void Graph::split(std::string line, std::vector<int> &res) {
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
  if (it != mapIP.end())
    ipIndex = it->second.getIpIndex();
  return ipIndex;
}

// Tiene una complejidad de O(V) donde V es el numero de vertices.
void Graph::loadGraph(std::string fileName) {
  std::string line, ip1, ip2, peso;
  int i = 0;
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  } else {
    while (std::getline(file, line)) {
      if (i == 0) {
        std::vector<int> res;
        split(line, res);
        numNodes = res[0];
        numEdges = res[1];
        // Reservar memoria para los renglones de la lista de adyacencia
        // Nodos son uno basados (renglon 0 no sera usado)
        adjList.resize(numNodes + 1);
        listaIP.resize(numNodes + 1);
        // Declarar una lista ligada vacia de pares (vertice, peso)
        // para cada renglon y se almacena en el vector
        for (int k = 1; k <= numNodes; k++) {
          LinkedList<std::pair<int, int>> tmpList;
          adjList[k] = tmpList;
        }
      } else if (i > 0 && i <= numNodes) {
        ipAddress tmpIP(line, i);
        mapIP.insert({tmpIP.getIpValue(), tmpIP});
        listaIP[i] = tmpIP;

        // std::cout << tmpIP << std::endl;
      } else if (i > numNodes) {
        std::size_t found = line.find(":", 15);
        ip1 = line.substr(15, found - 15);
        std::size_t found2 = line.find(" ", found + 1);
        std::size_t found3 = line.find(":", found2 + 1);
        ip2 = line.substr(found2, found3 - found2);
        std::size_t found4 = line.find(" ", found3 + 1);
        std::size_t found5 = line.find(" ", found4 + 1);
        peso = line.substr(found4, found5 - found4);
        // Crear arista ip1 a ip2 con un peso
        ipAddress tmpIP1(ip1, 0);
        ipAddress tmpIP2(ip2, 0);
        // ipAddress tmpIP2(ip2, 0);
        int ip1Index = findIpIndex(ip1);
        int ip2Index = findIpIndex(ip2);
        if (ip1Index != -1 && ip2Index != -1) {
          adjList[ip1Index].addLast({ip2Index, stoi(peso)});
          mapIP[tmpIP1.getIpValue()].addToOutDegree();
          mapIP[tmpIP2.getIpValue()].addtoInDegree();
        } else {
          throw std::out_of_range("Incorrect IPs in the edge");
          file.close();
        }
      }
      i++;
    }
    file.close();
  }
}

// Tiene una complejidad de O(V+E), donde donde E es el numero de aristas y V el
// de vertices
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

// Complejidad O(n), ya que recorre paso por paso todo el map con el fin de
// imprimir todas las IPs.
void Graph::printIPs() {
  std::cout << "IPs" << std::endl;
  std::map<unsigned int, ipAddress>::iterator it;
  for (it = mapIP.begin(); it != mapIP.end(); it++) {
    std::cout << it->second << std::endl;
  }
}

// Complejidad O(n), ya que debe recorrer todo el map para poder crear el
// macHeap necesario para almacenar cada IP con su grado de salida.
void Graph::crearHeap() {
  if (mapIP.size() == 0) {
    throw std::out_of_range("No hay elementos que almacenar.");
  }
  heapIP.setCapacity((int)mapIP.size());
  std::map<unsigned int, ipAddress>::iterator it;
  for (it = mapIP.begin(); it != mapIP.end(); it++) {
    GradoIP temp(it->second);
    heapIP.push(temp);
  }
  std::string bm = heapIP.top().getDireccion();
  bootmaster = findIpIndex(bm);
}

// Complejidad O(n) ya que recorre todo el heap con el fin de uno por uno irlo
// vaciando ya sea al archivo, o a pantalla en el caso del botMaster
void Graph::reporteIPs(std::string reporte, std::string top5) {
  int i = 0;
  int j = 0;
  if (heapIP.isEmpty()) {
    throw std::out_of_range("El max heap se encuentra vacio");
  } else {
    std::ofstream archivoImprime(reporte);
    std::ofstream archivoTop5(top5);
    if (!archivoImprime.good() && !archivoTop5.good()) {
      archivoImprime.close();
      archivoTop5.close();
      std::cout << "Archivos no encontrados" << std::endl;
    } else {
      while (j < mapIP.size() - 1) {
        archivoImprime << heapIP.top();
        if (i < 5) {
          if (i < 1) {
            std::cout << "Bootmaster:" << std::endl;
            std::cout << heapIP.top() << std::endl;
          }
          archivoTop5 << heapIP.top();
          i++;
        }
        heapIP.pop();
        j++;
      }
      archivoImprime << heapIP.top();
    }
    archivoImprime.close();
  }
}

// Usamos el algoritmo de dijkstra que tiene una complejidad de O(ELogV) donde E
// es el numero de aristas y V el de vertices
void Graph::dijkstraAlgorithm(std::string fileName) {
  // https://www.geeksforgeeks.org/implement-min-heap-using-stl/
  // pares (distancia, vertice)
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      pq;
  int src = bootmaster;
  // Create a vector for distances and initialize all
  // distances as infinite (INF)
  std::vector<int> dist(numNodes + 1, INF);
  // Insert source itself in priority queue and initialize
  // its distance as 0.
  pq.push(std::make_pair(0, src));
  dist[src] = 0;
  /* Looping till priority queue becomes empty (or all
  distances are not finalized) */
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    // 'i' is used to get all adjacent vertices of a
    // vertex
    // Recorremos los vertices vecinos de v
    NodeLinkedList<std::pair<int, int>> *ptr = adjList[u].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      int v = par.first;
      int weight = par.second;
      // If there is shorted path to v through u.
      if (dist[v] > dist[u] + weight) {
        // Updating distance of v
        dist[v] = dist[u] + weight;
        pq.push(std::make_pair(dist[v], v));
      }
      ptr = ptr->next;
    }
  }
  // Export the distances to a file
  std::ofstream outputFile(fileName);
  if (!outputFile.good()) {
    outputFile.close();
    throw std::invalid_argument("No se pudo abrir el archivo");
  } else {
    int maxDistance = dist[1];
    int maxIndex = 1;
    std::vector<std::pair<std::string, int>> ipDistances;
    for (auto it = mapIP.begin(); it != mapIP.end(); ++it) {
      outputFile << "Ip: " << it->second.getIp()
                 << " | Distancia: " << dist[it->second.getIpIndex()]
                 << std::endl;
      ipDistances.push_back(
          make_pair(it->second.getIp(), dist[it->second.getIpIndex()]));
      if (dist[it->second.getIpIndex()] > maxDistance) {
        maxDistance = dist[it->second.getIpIndex()];
        maxIndex = it->second.getIpIndex();
      }
    }
    std::cout << "Ip mas lejana: " << ipDistances[maxIndex - 1].first
              << " a una distancia de: " << maxDistance << std::endl;
    outputFile.close();
  }
}

void Graph::loadHashTable() {
  hashTable.setMaxSize(maxElementsHT);
  std::map<unsigned int, ipAddress>::iterator it;
  for (it = mapIP.begin(); it != mapIP.end(); it++) {
    hashTable.add(it->first, it->second);
  }
}

void Graph::printHT() { hashTable.printToFile("reporteHash.txt"); }

void Graph::getColisionesHT() {
  std::cout << "Colisiones en HT: " << hashTable.getColisiones() << std::endl;
}

void Graph::getIPSummary(std::string ip) {
  int i = 0;
  int index = findIpIndex(ip);
  if (index == -1) {
    throw std::out_of_range("No se encontro el elemento");
  } else {
    std::cout << "Resumen del IP: " << std::endl;
    ipAddress tmpIp(ip, 0);
    std::map<unsigned int, ipAddress>::iterator it;
    it = mapIP.find(tmpIp.getIpValue());
    if (it != mapIP.end())
      std::cout << it->second;
    std::cout <<std::endl;
    std::cout << "Hash index del IP buscado: "
              << hashTable.getHashIndex(it->second.getIpValue()) << std::endl;
    std::cout << "IPs accesadas desde esta IP (descendiente): " << std::endl;
    NodeLinkedList<std::pair<int, int>> *ptr = adjList[index].getHead();
    std::vector<ipAddress> ipsContact(adjList[index].getNumElements());
    // std::vector<std::pair<std::string,int>> vchoques;
    // int i=0;
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      ipsContact[i] = listaIP[par.first];
      i++;
      ptr = ptr->next;
    }
    std::sort(ipsContact.begin(), ipsContact.end(), std::greater<ipAddress>());
    for (int j = 0; j < ipsContact.size(); j++) {
      std::cout << ipsContact[j].getIp() << std::endl;
    }
    std::cout << std::endl;
  }
}