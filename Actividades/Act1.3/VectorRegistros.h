#ifndef _VECTORREGISTROS_H_
#define _VECTORREGISTROS_H_

#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Registro.h"

class VectorRegistros {

private:
  std::vector<Registro> registros;
  unsigned int compara, swap;
  int partition(int low, int high);
public:
  VectorRegistros();
  VectorRegistros(std::string nombreArchivo);
  ~VectorRegistros();
  int getSize();
  void imprime(std::string nombreArchivo);
  void bubbleSort();
  void quickSort(int low, int high);
  int binarySearch(std::string mes, std::string dia, std::string hora, std::string minuto, std::string segundo);
  void reporte();
  std::vector<Registro> reducir(int low, int high);
};

#endif //_VECTORREGISTROS_H_