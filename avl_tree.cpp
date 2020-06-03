/**************************************
 * ANDRIY KALINICHENKO
 * CS3610 - FALL 2019 
 * PROJECT 2
 * ************************************/

#include <iostream>
#include "avl_tree.h"
#include <algorithm>

using namespace std;
//  Insert functions given by insturctor, mostly unchanged.
void AVLTree::insert(const int key) {
  this->root = insert(key, this->root);
}

BinaryNode* AVLTree::insert(const int key, BinaryNode* node) {
  if (node == NULL) {
    return new BinaryNode(key);
  }

  if(key == node->key) cout<<"\nError, Duplicate node!";

  if(key < node->key) {
    if(node->left == NULL) {
      node->left = new BinaryNode(key); 
    } 
    else {
      node->left = insert(key, node->left);
    }
  }
  else {
    if(node->right == NULL) {
      node->right = new BinaryNode(key); 
    } 
    else {
      node->right = insert(key, node->right);
    }
  }
  //  Update the blance factor for the new node.
  node->bfactor = height(node->left) - height(node->right);
  //  These functions check for unblanced nodes, then calls the correct roation function accordingly.
  if(node->bfactor > 1 && node->left != NULL && key < node->left->key)  
    return right_rotate(node); 

  if(node->bfactor < -1 && node->right != NULL && key > node->right->key)  
    return left_rotate(node);

  if(node->bfactor > 1 && node->left != NULL && key > node->left->key){
    node->left = left_rotate(node->left);  
    return right_rotate(node);  
  } 
  
  if(node->bfactor < -1 && node->right != NULL && key < node->right->key){
    node->right = right_rotate(node->right);  
    return left_rotate(node);  
  } 
  
  return node;
}
//  Option sent to this function which then calls the recursive print function.
void AVLTree::print_tree(char option){

  int level = 0;

  if(root == NULL){ cout << "\nEmpty Tree!"; return;}

  rec_print(root, option, level);
}
//  Recursive print function
void AVLTree::rec_print(BinaryNode* root, char option, int level){

      if(root == NULL) return;
//  Recursive inorder traversal.
      if(option == 'p'){
 
          rec_print(root->left, option, level);
          std::cout<< " "<<root->key;
          rec_print(root->right, option, level);
      } 

// Recursive inorder traversal for printing height.
      if(option == 'h'){
  
          rec_print(root->left, option, level);
          cout <<" "<< height(root);
          rec_print(root->right, option, level);
      } 
}
// Calculates height of node, max function returns the deepest node of two subtrees then returns plus 1.
int AVLTree::height(BinaryNode* node){
    if(node == NULL) return 0;
    return max(height(node->left), height(node->right))+1;
}
// Rotation functions reblance the tree accordingly.
BinaryNode* AVLTree::left_rotate(BinaryNode* node){

  BinaryNode* previous_right = node->right;
  BinaryNode* previous_left = previous_right->left;

  previous_right->left = node;
  node->right = previous_left;

  return previous_right;
}

BinaryNode* AVLTree::right_rotate(BinaryNode* node){

  BinaryNode* previous_left = node->left;
  BinaryNode* previous_right = previous_left->right;

  previous_left->right = node;
  node->left = previous_right;

  return previous_left;
}

BinaryNode* AVLTree::remove_node(BinaryNode *root, int key){

  if(root == NULL)
    return root;

  // Go down left subtree to find matching key
  if(key < root->key){
    root->left = remove_node(root->left, key);
  // If it wasn't smaller, we must go down right subtree
  }else if(key > root->key){
    root->right = remove_node(root->right, key);
  //  This is the case where we find the key that needs to be deleted
  }else if(root->key == key){
  //  Check to see what children the node has 
    if((root->left == NULL) || (root->right == NULL)){
  //  Temporary placeholder node being created.
      BinaryNode* newnode;
  //  Storing one of the children in the placeholder.
      if(root->left){
        newnode = root->left;
      }else{ 
        newnode = root->right;
      }
  //  If this node had no chidlren the place holder will have remained as null.
      if(newnode == NULL){
        newnode = root;
        root = NULL;
      }else{ //  Now we copy over the node and delete it.
        *root = *newnode;
      }
      free(newnode);
    } else{
      //  Case for if the node had two children.
      BinaryNode *current = root->right;
      // We go all the way left in the right subtree wich gives us the smallest value node.
      while(current->left != NULL){
        current = current->left;
      }
      //  Copy the key with the smallest value node then we delete that subtree.
      BinaryNode *newnode = current;
      root->key = newnode->key;
      root->right = remove_node(root->right, newnode->key);
    }
  }
  if(root == NULL)
    return root;
  // Evaluate the balance factor of the new tree after deletion of node.
  root->bfactor = height(root->left) - height(root->right);
  // Here we do necessary rotations of new tree is unbalanced.
  if(root->bfactor > 1 && root->left->bfactor >= 0)  
    return right_rotate(root); 

  if(root->bfactor > 1 && root->left < 0){  
    root->left = left_rotate(root->left);
    return right_rotate(root);
  }

  if(root->bfactor < -1 && root->right->bfactor <= 0)
  return left_rotate(root);

  if(root->bfactor < -1 && root->right->bfactor > 0){
    root->right = right_rotate(root->right);
    return left_rotate(root);
  }
  return root;
}

void AVLTree::remove(int key){
  remove_node(root, key);
}