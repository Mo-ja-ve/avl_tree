/**************************************
 * ANDRIY KALINICHENKO
 * CS3610 - FALL 2019 
 * PROJECT 2
 * ************************************/

#include <iostream>
#include "avl_tree.h"
using namespace std;

int main() {

  AVLTree tree;

  char option;
  int key;

  do {
    cin >> option;
    switch(option) {
      case 'i':
        cin >> key;
        tree.insert(key);
        break;
      case 'r':
        cin >> key;
        tree.remove(key);
        break;  
      case 'h':
        tree.print_tree('h');
        cout<<endl;
        break;
      case 'p':
        tree.print_tree('p');
        cout<<endl;
        break;
      default:
        break;
    }
  } while(option != 'q');
}
