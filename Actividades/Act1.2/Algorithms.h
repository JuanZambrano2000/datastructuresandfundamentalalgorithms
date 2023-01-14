#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using std::vector;

class Algorithms {
private:
  void merge(vector<int> &A, int low, int m, int high, unsigned int &compara);
  int partition(vector<int> &values, int low, int high, unsigned int &compara,
                unsigned int &swap);

public:
  // AlgorithmSort();
  void randomShuffle(vector<int> &A);
  void printVector(vector<int> A);
  void bubbleSort(vector<int> &A, int n, unsigned int &compara,
                  unsigned int &swap);
  void mergeSort(vector<int> &A, int low, int high, unsigned int &compara);
  void quickSort(vector<int> &values, int low, int high, unsigned int &compara,
                 unsigned int &swap);
  int sequentialSearch(vector<int> &A, int key, unsigned int &compara);
  int binarySearch(vector<int> &A, int low, int high, int key,
                   unsigned int &compara);
};

// Mezcla los elementos del vector
//Complejidad en tiempo O(n) donde n es el número de elementos en el vector.
void Algorithms::randomShuffle(vector<int> &A) {
  std::shuffle(A.begin(), A.end(), std::random_device{});
}

// Imprime los elementos del vector
//Complejidad en tiempo O(n) donde n es el número de elementos en el vector.
void Algorithms::printVector(vector<int> A) {
  std::cout << "Los elementos del vector ordenado son: " << std::endl;
  for (int i = 0; i < (int)A.size(); i++) {
    std::cout << A[i] << " ";
  }
  std::cout << std::endl;
}

// SequentialSearch
//Complejidad en tiempo O(n) donde n es el número de elementos en el vector en el peor de los casos. En casos promedio tene una complejidad O(n/2) si encuentra el key en medio del arreglo.
int Algorithms::sequentialSearch(vector<int> &A, int key,
                                 unsigned int &compara) {
  compara = 0;
  for (int i = 0; i < (int)A.size(); ++i) {
    ++compara;
    if (A[i] == key) {
      return i;
    }
  }
  return -1;
}

// binarySearch
//Complejidad en tiempo O(log n) ya que el número de pasos sólamente incrementa cada vez que se dobla la cantidad de información en el arreglo. Requiere de un vector ordenado para poder contar con esta eficiencia. Si el vector no se encuentra ordenado se debe ordenar primero, llevándonos a una complejidad de O(n log n), por lo que es preferible la búsqueda secuencial en estos casos.
int Algorithms::binarySearch(vector<int> &A, int low, int high, int key,
                             unsigned int &compara) {
  int m;
  if (low > high)
    return -1;
  m = low + (high - low) / 2;
  compara++;
  if (key == A[m])
    return m;
  else if (key < A[m])
    return binarySearch(A, low, m - 1, key, compara);
  else
    return binarySearch(A, m + 1, high, key, compara);
}

// BubbleSort
//Bubble sort tiene una complejidad de O(n) en el mejor de los casos, donde todos los elementos estan acomodados de forma ascendente, O(n^2) en el caso promedio al igual del peor caso y no requiere de memoria extra para ejecutarse.
void Algorithms::bubbleSort(vector<int> &A, int n, unsigned int &compara,
                            unsigned int &swap) {
  compara = swap = 0;
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      compara++;
      if (A[j] > A[j + 1]) {
        std::swap(A[j], A[j + 1]);
        swap++;
      }
    }
  }
}

// mergeSort
//Merge sort tiene una complejidad de O(n log n) en todos los casos y necesita de O(n) de espacio en memoria para ejecutar.
void Algorithms::mergeSort(vector<int> &A, int low, int high,
                           unsigned int &compara) {
  if (low < high) {
    // encontrar el punto medio
    int m = low + (high - low) / 2;
    // Ordenar dos mitades
    mergeSort(A, low, m, compara);
    mergeSort(A, m + 1, high, compara);
    // Fusionar ambas mitades
    merge(A, low, m, high, compara);
  }
}

//Función que fusiona dos vectores ordenados y regresa un vector ordenado que contiene todos los elementos de ambos vectores. El análisis de complejidad de este vector está contenido en el análisis anterior de mergeSort.
void Algorithms::merge(vector<int> &A, int low, int m, int high,
                       unsigned int &compara) {
  int i, j, k;
  int n1 = m - low + 1;
  int n2 = high - m;
  // crear los vectores auxiliares L y R
  vector<int> L(n1);
  vector<int> R(n2);
  for (i = 0; i < n1; i++)
    L[i] = A[low + i];
  for (j = 0; j < n2; j++)
    R[j] = A[m + 1 + j];
  // Fusionar los vectores auxiliares Ly R ordenados
  i = j = 0;
  k = low;
  while (i < n1 && j < n2) {
    compara++;
    if (L[i] <= R[j]) {
      A[k] = L[i];
      i++;
    } else {
      A[k] = R[j];
      j++;
    }
    k++;
  }
  // Copia los elementos restantes
  while (i < n1) {
    A[k] = L[i];
    i++;
    k++;
  }
  while (j < n2) {
    A[k] = R[j];
    j++;
    k++;
  }
}

// quickSort
//Merge sort tiene una complejidad de O(n log n) en el mejor y promedio de los casos, en el peor caso es de O(n^2) cuando el vector esta ordenado del mas grande al mas pequeno, requiere O(log n) de espacio en memoria para ejecutarse.
void Algorithms::quickSort(vector<int> &A, int low, int high,
                           unsigned int &compara, unsigned int &swap) {
  if (low < high) {
    // encontrar la particion
    int pivot = partition(A, low, high, compara, swap);
    // ordenar la mitad izquierda y derecha
    quickSort(A, low, pivot - 1, compara, swap);
    quickSort(A, pivot + 1, high, compara, swap);
  }
}

// Coloca nuestro pivote en su posicion correcta y los elementos menores de este a la izquierda
int Algorithms::partition(std::vector<int> &A, int low, int high,
                          unsigned int &compara, unsigned int &swap) {
  int pivot = A[high];
  int i = low - 1;
  for (int j = low; j < high; j++) {
    compara++;
    if (A[j] < pivot) {
      i++;
      std::swap(A[i], A[j]);
      swap++;
    }
  }
  std::swap(A[i + 1], A[high]);
  return i + 1;
}

#endif // _ALGORITHMS_H_