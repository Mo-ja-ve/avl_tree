/**************************************
 * ANDRIY KALINICHENKO
 * CS3610 - FALL 2019 
 * PROJECT 2
 * ************************************/

#ifndef AVL_TREE_H
#define AVL_TREE_H

struct BinaryNode {
  BinaryNode(const int key) : key(key), left(NULL), right(NULL) {}

  ~BinaryNode() {
    delete left;
    delete right;
    //delete previous;
    left = right = NULL;
  }
  //int node_height = 0;
  int key;
  int bfactor = 0;
  BinaryNode *left, *right;
  //BinaryNode *previous;
};

class AVLTree {

public: 
  AVLTree() : root(NULL) {}
  ~AVLTree() { 
    delete root;
  }

  void print_tree(char option);
  void rec_print(BinaryNode* root, char option, int level);
  void insert(const int key);
  void write_height(BinaryNode* root);
  int  height(BinaryNode *root);
  //int find_bf(BinaryNode *root);
  int update_bf(BinaryNode *root);
  BinaryNode* left_rotate(BinaryNode *root);
  BinaryNode* right_rotate(BinaryNode *root);
  void remove(int key);
  BinaryNode* remove_node(BinaryNode *root, int key);
  //BinaryNode* max(int lheight, int rheight);
private:
  BinaryNode* insert(const int key, BinaryNode* node);
  BinaryNode* root;
};

#endif