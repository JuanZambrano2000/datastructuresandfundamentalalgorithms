/**
 * Ejemplo que implementa el factorial recursivo para un numero n
 *
 * Compilacion para debug:
 *    g++ -std=c++17 -Wall -g -o main *.cpp
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -O3 -o main *.cpp
 * Ejecucion:
 *    ./main
 **/
//Factorial de forma recursiva e iterativa

#include <iostream>

//unsigned long int tiene mas espacio para numero enteros positivos
//Forma recursiva
unsigned long int F(unsigned int n){
  if (n==0) return 1;
  return F(n-1)*n;
}
//Forma iterativa
unsigned long int Fite(unsigned int n){
  unsigned int retValue = 1;
  while (n!=0){
    retValue = retValue * n;
    n = n - 1;
  }
  return retValue;
}

int main() {
  std::cout << "Dame un numero positivo: " << std::endl;
  int n;
  std::cin >> n;
  std::cout << "Su factorial es: " << F(n) << std::endl;
  std::cout << "Su factorial es: " << Fite(n) << std::endl;
  return 0;
}