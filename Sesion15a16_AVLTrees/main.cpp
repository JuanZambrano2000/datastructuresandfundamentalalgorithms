/** 
* Ejemplo que implementa un AVL Tree (insert, remove, search) 
* y los recorridos inorder, postorder, y preorder
*
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -O3 -o main *.cpp 
* Ejecucion:
*    ./main
**/

#include <iostream>
#include "AVLTree.h"

int main() {
  std::cout << "Prueba de un AVL!\n";
  AVLTree<int> avl;
  std::cout << "insert(10), insert(20), insert(30), insert(40), insert(50), insert(25)" << std::endl;
  avl.insert(10);
  avl.insert(20);
  avl.insert(30);
  avl.insert(40);
  avl.insert(50);
  avl.insert(25);   
  /* 
    The constructed AVL Tree would be
            30
            / \
            20 40
            / \ \
          10 25 50
  */
  avl.print();
  
  // search
  std::cout << std::boolalpha << "search(10) " << avl.search(10) << std::endl;
  std::cout << std::boolalpha << "search(122) " << avl.search(122) << std::endl;
  
  // Borrar nodo con dos hijos
  std::cout << "remove(20) " << std::endl;
  avl.remove(20);
  avl.print();
  // Borrar nodo con un hijo
  std::cout << "remove(40) " << std::endl;
  avl.remove(40);
  avl.print();
  // Borrar nodo sin hijos
  std::cout << "remove(10) " << std::endl;
  avl.remove(10);
  avl.print();
  
  return 0;
}