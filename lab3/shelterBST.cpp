// Bryan Kim
// ShelterBST.cpp

#include <iostream>
#include <string>
#include "shelterBST.h"

//desc: inserts a node in the correct location of the BST
//pre : -assume there are no duplicates
//post: -returns new leaf node in its correct location
ShelterBST::TreeNode* ShelterBST::insert(TreeNode* root, Pet* pet) {
    if (root == nullptr) {
        return new TreeNode(pet);
    }
    if (root->pet->age < pet->age) {
        root->right = insert(root->right, pet);
    } else {
        root->left = insert(root->left, pet);
    }
    return root;
}

//desc: searches the BST for a node's age to match age
//pre : none
//post: -returns node if found, nullptr if not found
//      -else, returns recursive case
ShelterBST::TreeNode* ShelterBST::search(TreeNode* root, int age) {
    //if the node is empty return nullptr
    if (root == nullptr) {
        return nullptr;
    }
    
    //if node matches target reture root
    if (root->pet->age == age) {
        return root;
    }

    //if target > root, search the left
    if (root->pet->age > age) {
        return search(root->left,age);
    }
    //vice versa
    return search(root->right,age);
}

//desc: traverses and prints the BST's contents inorder (L->M->R)
//pre : none
//post: none
void ShelterBST::inorder(TreeNode* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->pet->name << ", " << root->pet->age << "   ";
        inorder(root->right);
    }
}

//desc: traverses and prints the BST's contents preorder (M->L->R)
//pre : none
//post: none
void ShelterBST::preorder(TreeNode* root) {
    if(root != nullptr) {
        cout << root->pet->name << ", " << root->pet->age << "   ";
        preorder(root->left);
        preorder(root->right);
    }
}

//desc: traverses and prints the BST's contents in postorder (L->R->M)
//pre : none
//post: none
void ShelterBST::postorder(TreeNode* root) {
    if(root != nullptr) {
        postorder(root->left);
        postorder(root->right);
        cout << root->pet->name << ", " << root->pet->age << "   ";
    }
}

//desc: ShelterBST default constructor
ShelterBST::ShelterBST() {
    root = nullptr;
}

//desc: runs the private insert method
//pre : none
//post: -sets root = return value of insert
void ShelterBST::insertPet(string name, int age) {
    root = insert(root, new Pet(name, age));
}

//desc: runs the private search method and prints a message
//pre : none
//post: -if the result == nullptr, print unable to findd
void ShelterBST::searchPet(int age) {
    TreeNode* result = search(root, age);
    if (result != nullptr) {
        cout << result->pet->name << " was found." << endl;
    } else {
        cout << "Pet not found." << endl;
    }
}

//desc: runs the private inorder method
void ShelterBST::inorderDisplay() {
    inorder(root);
}

//desc: runs the private preorder method
void ShelterBST::preorderDisplay() {
    preorder(root);
}

//desc: runs the private postorder method
void ShelterBST::postorderDisplay() {
    postorder(root);
}