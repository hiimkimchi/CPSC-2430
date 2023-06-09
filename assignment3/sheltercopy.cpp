// Bryan Kim
// ShelterBST.cpp

#include <iostream>
#include <string>
#include "ShelterBST.h"

//desc: inserts a node in the correct location of the BST by pet name
//pre : none
//post: -returns new leaf node in its correct location
//      -if pet is a duplicate, exit function
ShelterBST::TreeNode* ShelterBST::insert(TreeNode* root, Pet* pet) {
    //if empty make root
    if (root == nullptr) {
        return new TreeNode(pet);
    }
    //if node name < pet name, put on right
    if (root->pet->name < pet->name) {
        root->right = insert(root->right, pet);
    //else put on left
    } else {
        root->left = insert(root->left, pet);
    }
    return root;
}

//desc: searches the BST for a node's name to match name
//pre : none
//post: -returns node if found, nullptr if not found
//      -else, returns recursive case
ShelterBST::TreeNode* ShelterBST::search(TreeNode* root, string name) {
    //if the node is empty return nullptr
    if (root == nullptr) {
        return nullptr;
    }
    
    //if node matches target reture root
    if (root->pet->name == name) {
        return root;
    }

    //if target > root, search the left
    if (root->pet->name > name) {
        return search(root->left,name);
    }
    //vice versa
    return search(root->right,name);
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

//desc: returns the node of the parent of the key
//pre : none
//post: -returns node of the parent
//      -returns nullptr if the pet is at the root
ShelterBST::TreeNode* ShelterBST::parent(TreeNode* root, string name) {
    if (root == nullptr || root->pet->name == name) {
        return nullptr;
    }

    //do a search function again, but make the base case check the children
    if (root->right->pet->name == name || root->left->pet->name == name) {
        return root;
    }

    if (root->pet->name > name) {
        return parent(root->left,name);
    }
    return parent(root->right, name);
}

//desc: returns the inorder predecessor of a given pet (2 CHILDREN ONLY)
//pre : none
//post: -returns node of the inorder predecessor
//      -returns nullptr if the pet does not have 2 children
ShelterBST::TreeNode* ShelterBST::predecessor(TreeNode* root, string name){
    TreeNode* petNode = root;
    TreeNode* predNode = nullptr;

    if (petNode == nullptr) {
        return nullptr;
    }
    while (petNode != nullptr) {
        if (petNode->pet->name == name) {
            if (petNode->left != nullptr) {
                predNode = petNode->left;
                while(predNode->right != nullptr) {
                    predNode = predNode->right;
                }
            }
        petNode = nullptr;
        } else if (petNode->pet->name > name){
            petNode = petNode->left;
        } else {
            predNode = petNode;
            petNode = petNode->right;
        }
    }
    return predNode;
}

//desc: counts the total number of nodes in the tree
//pre : none
//post: -returns the number of nodes recursively
int ShelterBST::countNodes(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + countNodes(root->right) + countNodes(root->left);
}

//desc: counts the total number of internal nodes in the tree
//pre : -nodes counted must have 1 or two children
//post: -returns the number of internal nodes recursively
int ShelterBST::countInternalNodes(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    } else if(root->right == nullptr && root->left == nullptr) {
        return 0;
    }
    return 1 + countInternalNodes(root->right) + countInternalNodes(root->left);
}

//desc:
//pre :
//post:
int ShelterBST::nodesInLevel(TreeNode* root, int level) {
    //check for empty tree and level at root
    if (root == nullptr) {
        return 0;
    }
    if (level == 0) {
        return 1;
    }
    //level order traversal?
    //FINISH
    return 0;
}

//desc: finds the height of a BST
//pre : none
//post: -returns the max height between right and left subtrees recursively
int ShelterBST::height(TreeNode* root) {
    //checks if tree exists
    if (root == nullptr) {
        return 0;
    }

    //compares the heights of the subtrees, and returns the bigger one
    int leftSubtree = height(root->left);
    int rightSubtree = height(root->right);
    if (leftSubtree >= rightSubtree) {
        return leftSubtree + 1;
    } else {
        return rightSubtree + 1;
    }
}

//desc: checks if the BST is balanced
//pre : none
//post: -if difference between right and left subtrees is between -1 and 1 inclusive, return true
//      -if tree is empty return true
//      -returns false otherwise.
bool ShelterBST::isBalanced(TreeNode* root) {
    if (root == nullptr) {
        return true;
    }
    //check if the -1 <= difference between left and right <= 1 and recursively checks right and left subtrees 
    int leftSubtree = height(root->left);
    int rightSubtree = height(root->right);
    int diff = leftSubtree - rightSubtree;
    if ((diff <= 1 || diff == -1) && isBalanced(root->left) && isBalanced(root->right)) {
        return true;
    }
    return false;
}

//desc: deletes a node from the BST
//pre : none
//post: -if there are no children, delete the node
//      -if there is 1 child, delete the node and link the child to the tree
//      -if there are 2 children, delete the node and replace it with the inorder predecessor
ShelterBST::TreeNode* ShelterBST::deleteNode(TreeNode* root, string name) {
    TreeNode* petNode = nullptr;
    TreeNode* temp = nullptr;
    TreeNode* searched = search(root, name);
    //if tree empty return nullptr
    if (root == nullptr) {
        return nullptr;
    }
    
    if (root->pet->name == name) {
        //no children
        if (root->right == nullptr && root->left == nullptr) {
            return root;
        }
        //one right child
        if (root->right != nullptr && root->left == nullptr) {
            petNode = parent(root, name);
            petNode->right = root->right;
            return root;
        }
        //one left child
        if (root->left != nullptr && root->right == nullptr) {
            petNode = parent(root,name);
            petNode->left = root->left;
            return root;
        }
        //two children
        petNode = predecessor(root, name);
        root->pet = petNode->pet;
        temp = deleteNode(root->left, name);
        return temp;
    }
    //recursive cases
    return nullptr;
    //FINISH
}

ShelterBST::TreeNode* ShelterBST::destroy(TreeNode* root) {
    //base case
    if (root == nullptr) {
        return nullptr;
    }
    //delete nodes in postorder
    destroy(root->left);
    destroy(root->right);
    delete root;
    return nullptr;
}


//desc: ShelterBST default constructor
ShelterBST::ShelterBST() {
    root = nullptr;
}

//desc: ShelterBST destructor
ShelterBST::~ShelterBST() {
    destroy(root);
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
void ShelterBST::searchPet(string name) {
    TreeNode* result = search(root, name);
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

//desc: runs the private parent node method 
void ShelterBST::petParent(string name) {
    TreeNode* petNode = parent(root, name);
    cout << endl <<name << "\'s parent node is " << petNode->pet->name << ", " << petNode->pet->age << ".";
}

//desc: runs the private predecessor method
void ShelterBST::petPredecessor(string name) {
    TreeNode* petNode = predecessor(root, name);
    if (petNode != nullptr) {
        cout << name << "\'s inorder predecessor node is " << petNode->pet->name << ", " << petNode->pet->age << ".";
    } else {
        cout << endl << "There is no predecessor.";
    }
}

//desc: runs the private countNodes method
void ShelterBST::countPets() {
    int total = countNodes(root);
    cout << endl << "There are " << total << " pets in the tree.";
}

//desc: runs the private countInternalNodes method
void ShelterBST::countInternalPets(){
    int total = countInternalNodes(root);
    cout << endl << "There are " << total << " pets in the internal nodes of the tree.";
}

//desc: runs the private nodesInLevel method
void ShelterBST::printInLevel(int level) {
    int total = nodesInLevel(root, level);
    cout << endl << "There are " << total << " pets in level " << level << " of the tree.";
}

//desc: runs the private height method
void ShelterBST::printHeight() {
    int nodeHeight = height(root);
    cout << endl << "The height of the tree is " << nodeHeight << ".";
}

//desc: runs the private isBalanced method
void ShelterBST::printBalanced() {
    if (isBalanced(root)) {
        cout << endl << "The tree is balanced.";
    } else {
        cout << endl << "The tree is not balanced.";
    }
}

//desc: runs the private deleteNode method
void ShelterBST::deletePet(string name) {
    TreeNode* petNode = deleteNode(root, name);
    if (petNode != nullptr) {
        delete petNode;
        cout << endl << name << " has been deleted from the tree.";
    } else {
        cout << endl << name << " is not in the tree, so it has not been deleted.";
    }
}

//desc: runs the private destroy method
void ShelterBST::destroyTree() {
    //should return nullptr
    TreeNode* petNode = destroy(root);
    if (petNode == nullptr) {
        cout << endl << "The tree has successfully been destroyed.";
    } else {
        cout << endl << "Error. Tree destroying unsuccessful.";
    }
}