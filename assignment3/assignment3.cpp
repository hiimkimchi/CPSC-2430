// Bryan Kim
// assignment3.cpp
// This code implements a user made binary search tree that contains pet members.

#include <iostream>
#include <string>
#include "ShelterBST.h"

using namespace std;

//desc: prints the menu
//pre : none
//post: none
void printMenu();

//desc: tests all the functions
//pre : none
//post: none
void test(ShelterBST root);

int main() {
    ShelterBST tree, testTree;
    int option = -1, age = 0, level = 0;
    string name = "";
    while (option != 0) {
        printMenu();
        cin >> option;
        switch (option) {
            case 1:
                cout << endl << "Please input your pet's name: ";
                cin >> name;
                cout << endl << "Please input your pet's age: ";
                cin >> age;
                tree.insertPet(name, age);
                cout << endl << "You have added " << name << " to the tree." << endl;
                break;
            case 2:
                cout << endl << "Please input the name of the pet you want to search for: ";
                cin >> name;
                tree.searchPet(name);
                break;
            case 3:
                cout << endl << "Inorder Traversal:" << endl;
                tree.inorderDisplay();
                break;
            case 4:
                cout << endl << "Preorder Traversal:" << endl;
                tree.preorderDisplay();
                break;
            case 5:
                cout << endl << "Postorder Traversal:" << endl;
                tree.postorderDisplay();
                break;
            case 6:
                cout << endl << "Please input the name of the pet you want to find the parent of: ";
                cin >> name;
                tree.petParent(name);
                break;
            case 7:
                cout << endl << "Please input the name of the pet you want to find the inorder predecessor for: ";
                cin >> name;
                tree.petPredecessor(name);
                break;
            case 8:
                tree.countPets();
                break;
            case 9:
                tree.countInternalPets();
                break;
            case 10:
                cout << endl << "Please input the level you want to count the nodes in: ";
                cin >> level;
                tree.printInLevel(level);
                break;
            case 11:
                tree.printHeight();
                break;
            case 12:
                tree.printBalanced();
                break;
            case 13:
                cout << endl << "Please input the name of the pet you want to delete: ";
                cin >> name;
                tree.deletePet(name);
                break;
            case 14:
                tree.destroyTree();
                cout << endl;
                break;
            case 15:
                test(testTree);
                break;
            case 0:
                cout << endl << "Thank you for accessing my ShelterBST implementation.";
                tree.destroyTree();
                cout << endl << endl;
                return 0;
            default:
                cout << endl << "Command not recognized." << endl;
        }
    }
    return 0;
}

void printMenu() {
    cout << endl << "Welcome to my implementation of ShelterBST\nPlease choose the operation you want: " << endl << endl
         << "1.  Insert a node\n2.  Search for a node\n3.  Inorder Traversal\n4.  Preorder Traversal" << endl
         << "5.  Postorder Traversal\n6.  Find a node's parent\n7.  Find a node's inorder predecessor" << endl
         << "8.  Count all nodes\n9.  Count all internal nodes\n10. Count nodes in a certain level" << endl
         << "11. Find the height of the tree\n12. Check if tree is balanced\n13. Delete a pet from the tree" << endl
         << "14. Destroy the tree\n15. Test functionality (WARNING this will create a new tree)" << endl
         << "0.  Exit" << endl;
}

void test(ShelterBST tree) {
    //insert 10 pets (at least 1 duplicate name)
    tree.insertPet("Emily", 32);
    tree.insertPet("Tiny", 2);
    tree.insertPet("Jumba", 16);
    tree.insertPet("Lala", 24);
    tree.insertPet("Jacob", 5);
    tree.insertPet("Helen", 20);
    tree.insertPet("Okok", 61);
    tree.insertPet("Emily", 21);
    tree.insertPet("Ali", 35);
    tree.insertPet("Zumba", 7);

    //search for Tiny
    cout << endl << "Searching for: \"Tiny\"" << endl;
    tree.searchPet("Tiny");

    //inorder traversal
    cout << endl << "Inorder Traversal: " << endl;
    tree.inorderDisplay();

    //preorder traversal
    cout << endl << endl << "Preorder Traversal: " << endl;
    tree.preorderDisplay();

    //postorder traversal
    cout << endl << endl << "Postorder Traversal: " << endl;
    tree.postorderDisplay();

    //find parent of Jacob
    cout << endl << endl << "Parent node of: \"Jacob\"";
    tree.petParent("Jacob");

    //predcessor of Zumba
    cout << endl << endl << "Predecessor of \"Jacob\"" << endl;
    tree.petPredecessor("Jacob");

    //total number of nodes
    cout << endl << endl;
    tree.countPets();

    //total number of internal nodes
    cout << endl << endl;
    tree.countInternalPets();

    //total number of nodes in level 2
    cout << endl << endl;
    tree.printInLevel(2);

    //print height of the tree
    cout << endl << endl;
    tree.printHeight();

    //print if the tree is balanced or not
    cout << endl << endl;
    tree.printBalanced();

    //delete Jumba and print a message confirming it
    cout << endl << endl;
    tree.deletePet("Lala");

    //destroy the tree and confirm it is destroyed
    cout << endl;
    tree.destroyTree();
    cout << endl << endl;
}