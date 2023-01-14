 /*
  * Algoritmos de busqueda
  * 
  * Compilación:
  *  g++ -std=c++17 *.cpp -Wall -g -o main
  *
  * Ejecución:
  *  ./main < TestCases/test01.txt
  *  ./main < TestCases/test03.txt > salida.txt
  */
//Created and compiled in replit.com

#include <iostream>
#include <vector>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int busquedaSecuencial(std::vector<int> &A, int key, int &compara) {
  compara = 0;
  for (int i = 0; i < (int)A.size(); ++i) {
    ++compara;
    if (A[i] == key) {
      return i;
    }
  }
  return -1;
}
int busquedaSecuencialVectorOrdenado(std::vector<int> &A, int key, int &compara) {
  compara = 0;
  for (int i = 0; i < (int)A.size(); ++i) {
    ++compara;
    if (key<=A[i]) {
      if(key==A[i])
        return i;
      else 
        return -1;
    }
  }
  return -1;
}

int busquedaBinaria(std::vector<int> &A, int key, int &compara) {
  int low = 0;
  int high = (int)A.size()-1;
  int mid = 0;
  while(low <= high) {
    mid = (low + high)/2;
    compara += 1;
    if (key == A[mid]) {
      return mid;
    } else if (key < A[mid]) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return -1;
}

int binarySearchRecursive(vector<int> &A, int low, int high, int key, int &compara){
  int m;
  if (low > high) return -1;
  m = low + (high -low)/2;
  compara++;
  if (key == A[m]) return m;
  else if (key < A[m]) 
      return binarySearchRecursive(A, low, m - 1, key, compara);
  else 
    return binarySearchRecursive(A, m + 1, high, key, compara);
}

int main() {
  int i, tmp, size, key, flag;
  // Inicio conteo de tiempo de ejecución  
  auto startTime = std::chrono::high_resolution_clock::now();
  cin >> size; 
  cout << "Size: " << size << endl;
  cin >> key;
  cout << "Key: " << key << endl;
  cin >> flag;
  cout << "Print flag: " << flag << endl;
  // Declaración del 
  std::vector<int> myVector;
  // Lectura de los elementos del arreglo
  for(i = 0; i < size; i++) {
     cin >> tmp;
     myVector.push_back(tmp);
  }
  if (flag) {
    cout << "Los elementos del arreglo son: " << endl;
    for(i = 0; i < size; i++) {
      cout << myVector[i] << " ";
    }
    cout << endl;
  }
  int comparaciones = 0;
  //cout << "Key buscado esta en indice: " <<    busquedaSecuencial(myVector, key, comparaciones) << endl;
  //cout << "Key buscado esta en indice: " <<    busquedaSecuencialVectorOrdenado(myVector, key, comparaciones) << endl;
  //cout << "Key buscado esta en indice: " <<    busquedaBinaria(myVector, key, comparaciones) << endl;
  cout << "Key buscado esta en indice: " <<    binarySearchRecursive(myVector, 0, (int)myVector.size()-1, key, comparaciones) << endl;
  // Termina conteo de tiempo de ejecución 
  auto endTime = std::chrono::high_resolution_clock::now();
  auto totalTime = endTime - startTime;

  cout << "Tiempo de ejecución en ms: " << totalTime/std::chrono::milliseconds(1) << endl;
  cout << "Numero de comparaciones: " << comparaciones << endl;
  return 0;
}
