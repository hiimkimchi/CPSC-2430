// Bryan Kim
// ShelterBST.h
#ifndef SHELTERBST_H
#define SHELTERBST_H
#include <string>

using namespace std;

class ShelterBST {
    private:
        struct Pet {
            string name;
            int age;
            Pet(string name, int age) {
                this->name = name;
                this->age = age;
            }
        };

        struct TreeNode {
            Pet* pet;
            TreeNode* left;
            TreeNode* right;
            TreeNode(Pet* pet) {
                this->pet = pet;
                left = nullptr;
                right = nullptr;
            }
        };
        TreeNode* root;

        TreeNode* insert(TreeNode* root, Pet* pet);
        TreeNode* search(TreeNode*root, string name);
        void inorder(TreeNode* root);
        void preorder(TreeNode* root);
        void postorder(TreeNode* root);
        TreeNode* parent(TreeNode* root, string name);
        TreeNode* predecessor(TreeNode* root, string pet);
        int countNodes(TreeNode* root);
        int countInternalNodes(TreeNode* root);
        int nodesInLevel(TreeNode* root, int level);
        int height(TreeNode* root);
        bool isBalanced(TreeNode* root);
        TreeNode* deleteNode(TreeNode* root, string name);
        TreeNode* destroy(TreeNode* root); 

    public:
        ShelterBST();
        void insertPet(string name, int age);
        void searchPet(string name);
        void inorderDisplay();
        void preorderDisplay();
        void postorderDisplay();
        void petParent(string name);
        void petPredecessor(string name);
        void countPets();
        void countInternalPets();
        void printInLevel(int level);
        void printHeight();
        void printBalanced();
        void deletePet(string name);
        void destroyTree();

};
#endif /*SHELTERBST_H*/
