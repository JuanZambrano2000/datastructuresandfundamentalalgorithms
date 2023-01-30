#ifndef _DLLREGISTROS_H_
#define _DLLREGISTROS_H_

#include "DLinkedList.h"
#include "Registro.h"
#include <fstream>
#include <stdexcept>
#include <string>

class DLLRegistro {
private:
  DLinkedList registros;

public:
  DLLRegistro();
  DLLRegistro(std::string nombreArchivo);
  ~DLLRegistro();
  int getSize();
  void printToConsole();
  void printToTextFile(std::string nombreArchivo);
  void quickSort();
  void mergeSort();
  
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

void DLLRegistro::printToConsole() {
  if (registros.getNumElements() <= 0)
    throw std::out_of_range("Lista vacia");
  else {
    for (int i = 0; i < registros.getNumElements() - 1; i++) {
      std::cout << registros.getData(i) << std::endl;
    }
  }
}

void DLLRegistro::printToTextFile(std::string nombreArchivo) {
  if (registros.getNumElements()<=0) {
    throw std::out_of_range("La lista esta vacia");
  } 
  else {
    std::ofstream archivoImprime(nombreArchivo);
    if (!archivoImprime.good()) {
      archivoImprime.close();
      std::cout << "Archivo no encontrado" << std::endl;
    }
    else {
      for(int i=0; i < registros.getNumElements() - 1; i++) {
        archivoImprime << registros.getData(i) << std::endl;
      }
    }
    archivoImprime.close();
  }  
}

void DLLRegistro::quickSort() {registros.quickSort();}

void DLLRegistro::mergeSort() {registros.mergeSort();}


#endif //_DLLREGISTROS_H_