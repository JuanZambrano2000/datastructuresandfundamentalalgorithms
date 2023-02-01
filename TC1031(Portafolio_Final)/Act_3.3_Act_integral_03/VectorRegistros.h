#ifndef _VECTORREGISTROS_H_
#define _VECTORREGISTROS_H_

#include "IPs.h"
#include "MaxHeap.h"
#include "Registro.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

class VectorRegistros {

private:
  // Vector de registros que guarda todos los elementos del archivo txt
  std::vector<Registro> registros;
  // MAXHEAP
  MaxHeap<IPs> heapIP;
  // Variables que usamos para guardar las comparaciones y swaps de los
  // algoritmos de ordenamiento y busqueda
  unsigned int compara, swap;
  // Metodo del quicksort
  int partition(int low, int high);
  //n - tamano del vector, i posicion
  void heapify(int n, int i);

public:
  // Constructores
  VectorRegistros();
  VectorRegistros(std::string nombreArchivo);
  // destructor
  ~VectorRegistros();
  // regresa el tamano
  int getSize();
  void imprime(std::string nombreArchivo);
  // Algoritmos de busqueda y ordenamiento
  void bubbleSort();
  void quickSort(int low, int high);
  int binarySearch(std::string mes, std::string dia, std::string hora,
                   std::string minuto, std::string segundo);
  void reporte();
  std::vector<Registro> reducir(int low, int high);
  Registro getData(int i);
//heap sort
  void heapSort();
  void contarRepeticiones();
  void reporteIPs(std::string nombreArchivo);
};

#endif //_VECTORREGISTROS_H_