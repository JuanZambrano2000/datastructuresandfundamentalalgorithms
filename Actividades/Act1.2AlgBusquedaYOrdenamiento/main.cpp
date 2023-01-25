/**
 * Actividad 1.2, implementacion de los algoritmos de busqueda:
 * Busqueda binaria y busqueda secuencial de forma ordenada y sin ordenar,
 * y algoritmos de ordenamiento:
 * bubbleSort, quickSort y mergeSort
 * Hecho por los Alumnos:
 * Juan Pablo Zambrano Barajas A01636420
 * Samuel García Berenfeld A01642317
 * TC1031 con el profesor Eduardo Tello
 * Creado el 13/01/2023, ultima modificacion 14/01/2023
 * Compilar:
 *   g++ -std=c++17 -Wall -O3 *.cpp -o main
 * Ejecutar:
 *   ./main < TestCases/t1.txt
 *   ./main < TestCases/t1.txt > salida.txt
 */

#include "Algorithms.h"
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

int main() {
  int size, sortChoice, searchChoice, key;
  unsigned int comparisons, swaps;
  // Creamos instancia de la clase para poder usar los metodos
  Algorithms vec;
  // Guardamos el tamano del vector, el algoritmo de ordenamiento a usar, el
  // dato a buscar y el dato a buscar
  cin >> size;
  cout << "Size: " << size << endl;
  cin >> sortChoice;
  cout << "Sort algorithm choice: " << sortChoice << endl;
  cin >> searchChoice;
  cout << "Search algorithm choice: " << searchChoice << endl;
  cin >> key;
  cout << "Data to search: " << key << endl;
  // Creacion del vector con los datos
  vector<int> myVector(size);
  // Llenado del vector con los datos
  for (int i = 0; i < size; i++) {
    cin >> myVector[i];
  }
  cout << "Proceso de ordenamiento" << endl;
  if (sortChoice == 1) {
    vec.bubbleSort(myVector, size, comparisons, swaps);
    vec.printVector(myVector);
    cout << "Numero de comparaciones: " << comparisons << endl;
    cout << "Numero de intercambios: " << swaps << endl;
  } else if (sortChoice == 2) {
    vec.mergeSort(myVector, 0, size - 1, comparisons);
    vec.printVector(myVector);
    cout << "Numero de comparaciones: " << comparisons << endl;
    cout << "MergeSort no hace swaps" << endl;
  } else if (sortChoice == 3) {
    vec.quickSort(myVector, 0, size - 1, comparisons, swaps);
    vec.printVector(myVector);
    cout << "Numero de comparaciones: " << comparisons << endl;
    cout << "Numero de intercambios: " << swaps << endl;
  } else {
    cout << "Algoritmo de ordenamiento no definido" << endl;
  }
  comparisons = 0;
  cout << "Proceso de busqueda" << endl;
  if (searchChoice == 1) {
    cout << "Indice de la key: "
         << vec.sequentialSearch(myVector, key, comparisons) << endl;
    cout << "Numero de comparaciones: " << comparisons << endl;
  } else if (searchChoice == 2) {
    cout << "Indice de la key: "
         << vec.binarySearch(myVector, 0, myVector.size() - 1, key, comparisons)
         << endl;
    cout << "Numero de comparaciones: " << comparisons << endl;
  } else {
    cout << "Algoritmo de besqueda no definido" << endl;
  }
  return 0;
}