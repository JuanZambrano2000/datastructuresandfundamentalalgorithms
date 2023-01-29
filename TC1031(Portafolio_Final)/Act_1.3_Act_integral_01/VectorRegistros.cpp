#include "VectorRegistros.h"

VectorRegistros::VectorRegistros() {}

VectorRegistros::VectorRegistros(std::string nombreArchivo) {
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
      registros.push_back(temp);
    }
    archivo.close();
  }
}

VectorRegistros::~VectorRegistros() {
}
//regresamos el tamano del texto
int VectorRegistros::getSize() { return registros.size(); }

/*
void VectorRegistros::imprime() {
  if (registros.empty()) {
    std::cout << "No hay registros en el vector B)" << std::endl;
  } else {
    for (int i = 0; i < registros.size(); i++) {
      std::cout << registros[i].getAll() << std::endl;
    }
  }
}
*/
//Crea el archivo de salida 
void VectorRegistros::imprime(std::string nombreArchivo) {
  
  if (registros.empty()) {
    std::cout << "No hay registros en el vector B)" << std::endl;
  } 
  else {
    std::ofstream archivoImprime(nombreArchivo);
    if (!archivoImprime.good()) {
      archivoImprime.close();
      std::cout << "Archivo no encontrado" << std::endl;
    }
    else {
      for(int i=0; i < registros.size(); i++) {
        archivoImprime << registros[i].getAll() << std::endl;
      }
    }
    archivoImprime.close();
  }  
}

// Algoritmo ineficiente
void VectorRegistros::bubbleSort() {
  compara = swap = 0;
  int tam = registros.size();
  Registro dummy;
  for (int i = 0; i < tam - 1; i++) {
    for (int j = 0; j < tam - i - 1; j++) {
      compara++;
      if (registros[j] > registros[j + 1]) {
        std::swap(registros[j], registros[j + 1]);
        swap++;
      }
    }
  }
}
//Algoritmo eficiente
void VectorRegistros::quickSort(int low, int high) {
  if (low < high) {
    int pivote = partition(low, high);
    quickSort(low, pivote - 1);
    quickSort(pivote + 1, high);
  }
}

int VectorRegistros::partition(int low, int high) {
  Registro pivote = registros[high];
  int i = low - 1;
  for (int j = low; j < high; j++) {
    compara++;
    if (registros[j] < pivote) {
      i++;
      std::swap(registros[i], registros[j]);
      swap++;
    }
  }
  std::swap(registros[i + 1], registros[high]);
  return i + 1;
}
//Algoritmo para buscar las fechas
int VectorRegistros::binarySearch(std::string mes, std::string dia,std::string hora, std::string minuto, std::string segundo) {
  Registro dummy(mes, dia, hora, minuto, segundo);
  int low = 0;
  int high = (int)registros.size();
  int mid = 0;
  while (low <= high) {
    mid = (low + high) / 2;
    compara++;
    if (dummy == registros[mid]) {
      return mid;
    } else if (dummy < registros[mid]) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return -1;
}
//Nos dice los swaps y comparaciones de los algoritmos de ordenamiento
void VectorRegistros::reporte() {
  std::cout << "Numero de comparaciones hasta ahora: " << compara << std::endl;
  std::cout << "Numero de intercambios hasta ahora: " << swap << std::endl << std::endl;
  compara = 0, swap = 0;
}

std::vector<Registro> VectorRegistros::reducir(int low, int high){
  std::vector<Registro> nuevo;
  for(int i=low; i<=high; i++){
    nuevo.push_back(registros[i]);
  }
  return nuevo;
}

