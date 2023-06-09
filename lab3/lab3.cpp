// Bryan Kim
// lab3.cpp
// This code creates a BST containing Pet members

#include <iostream>
#include "shelterBST.h"

int main() {
    ShelterBST tree;
    
    //1. insert 10 pets into the BST
    tree.insertPet("Zelda", 5);
    tree.insertPet("Link", 7);
    tree.insertPet("Ganon", 12);
    tree.insertPet("Sheik", 6);
    tree.insertPet("Hyrule", 25);
    tree.insertPet("Sword", 2);
    tree.insertPet("Shield", 1);
    tree.insertPet("Bow", 3);
    tree.insertPet("Bomb", 4);
    tree.insertPet("Triforce", 30);

    //2. display the three traversals
    cout << endl << "Inorder Traversal: " << endl;
    tree.inorderDisplay();

    cout << endl << endl << "Preorder Traversal: " << endl;
    tree.preorderDisplay();

    cout << endl << endl << "Postorder Traversal: " << endl;
    tree.postorderDisplay();
    cout << endl << endl;

    //3. successful and unsuccessful search respectively
    //"Link was found."
    tree.searchPet(7);
    //"Pet not found."
    tree.searchPet(40);
    cout << endl;

    return 0;
}