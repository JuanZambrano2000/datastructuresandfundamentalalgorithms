#ifndef _DLLREGISTROS_H_
#define _DLLREGISTROS_H_

#include "DLinkedList.h"
#include "Registro.h"
#include <fstream>
#include <stdexcept>
#include <string>

class DLLRegistro : public DLinkedList {
  // private:
  // DLinkedList registros;

public:
  DLinkedList registros;
  DLLRegistro();
  DLLRegistro(std::string nombreArchivo);
  ~DLLRegistro();
  int getSize();
  void printToConsole();
  void printToTextFile(std::string nombreArchivo);
  void quickSort();
  void mergeSort();
  void binarySearch(Registro value);
  int getPosicionElemento();
  void resetPosicionElemento();
  // DLinkedList getSublist(int start, int end);
  void printSubListToTextFile(std::string nombreArchivo, int start, int end);
  int getComparaciones();
};

DLLRegistro::DLLRegistro() {}
DLLRegistro::~DLLRegistro() {}

DLLRegistro::DLLRegistro(std::string nombreArchivo) {
  std::string mes, dia, horas, minutos, segundos, ip, puerto, falla;
  std::ifstream archivo(nombreArchivo);
  if (!archivo.good()) {
    archivo.close();
    throw std::invalid_argument("Archivo no encontrado :(");
  } else {
    while (!archivo.eof()) {
      std::getline(archivo, mes, ' ');
      // if (mes.lenght == 0) break;
      std::getline(archivo, dia, ' ');
      std::getline(archivo, horas, ':');
      std::getline(archivo, minutos, ':');
      std::getline(archivo, segundos, ' ');
      std::getline(archivo, ip, ':');
      std::getline(archivo, puerto, ' ');
      std::getline(archivo, falla);
      // Se crea un registro nuevo con lo leído.
      Registro temp(mes, dia, horas, minutos, segundos, ip, puerto, falla);
      // Metemos al registro temporal a nuestro vector
      registros.addFirst(temp);
    }
    archivo.close();
  }
}

int DLLRegistro::getSize() { return registros.getNumElements(); }

//Tiene un tiempo de ejecucion de O(n), en el mejor, peor y caso promedio, pues tenemos que recorrer toda la lista para imprimir a la consola
void DLLRegistro::printToConsole() {
  if (registros.getNumElements() <= 0)
    throw std::out_of_range("Lista vacia");
  else {
    DLLNode *p = registros.getHead();
    while (p != nullptr) {
      std::cout << registros.getData(p) << std::endl;
      p = p->next;
    }
  }
}

//Tiene un tiempo de ejecucion de O(n), en el mejor, peor y caso promedio, pues tenemos que recorrer toda la lista para llenar el archivo
void DLLRegistro::printToTextFile(std::string nombreArchivo) {
  if (registros.getNumElements() <= 0) {
    throw std::out_of_range("La lista esta vacia");
  } else {
    std::ofstream archivoImprime(nombreArchivo);
    if (!archivoImprime.good()) {
      archivoImprime.close();
      std::cout << "Archivo no encontrado" << std::endl;
    } else {
      DLLNode *p = registros.getHead();
      while (p != nullptr) {
        archivoImprime << registros.getData(p) << std::endl;
        p = p->next;
      }
      archivoImprime.close();
    }
  }
}

//Tiene un tiempo de ejecucion de O(n), en el mejor, peor y caso promedio, pues tenemos que recorrer toda la lista para llenar el archivo. Aunque imprima una sublista, recorre toda la lista hasta el fin de la misma para hacerlo.
void DLLRegistro::printSubListToTextFile(std::string nombreArchivo, int start, int end) {
  if (registros.getNumElements() <= 0) {
    throw std::out_of_range("La lista esta vacia");
  } else {
    if (start >= 0 && end <= registros.getNumElements()) {
      std::ofstream archivoImprime(nombreArchivo);
      if (!archivoImprime.good()) {
        archivoImprime.close();
        std::cout << "Archivo no encontrado" << std::endl;
      } else {
        archivoImprime << "Resultado de la búsqueda: " << std::endl <<std::endl;
        archivoImprime << "Registros: " << (end-start)+1 << std::endl <<std::endl;
        DLLNode *p = registros.getHead();
        int index = 0;
        while (p != nullptr && index <= end) {
          if (index >= start && index <= end) {
            archivoImprime << registros.getData(p) << std::endl;
          }
          index++;
          p = p->next;
        }
      }
      archivoImprime.close();
    }
  }
}

void DLLRegistro::quickSort() { registros.quickSort(); }

void DLLRegistro::mergeSort() { registros.mergeSort(); }

void DLLRegistro::binarySearch(Registro value) {
  registros.binarySearch(value);
}

int DLLRegistro::getPosicionElemento() {
  return registros.getPosicionElemento();
}

void DLLRegistro::resetPosicionElemento() { registros.resetPosicionElemento(); }

int DLLRegistro::getComparaciones(){
  return registros.getComparaciones();
}

#endif //_DLLREGISTROS_H_