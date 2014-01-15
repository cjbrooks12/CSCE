#include "BinaryNode.h"


class BinarySearchTree {
private:
    BinaryNode *root;
    
public:
    BinarySearchTree() { root = NULL; }
    BinarySearchTree(int key) { root = new BinaryNode(key); }
    BinarySearchTree(BinaryNode *mRoot) { root = mRoot; }
    
    bool isEmpty() {return root == NULL; }
    BinaryNode* getRoot() { return root; }
    int size() { return (root==NULL) ? 0 : root->size(root); }
    int height() { return (root==NULL) ? 0 : root->height(root); }
    void print() { if(root != NULL) root->print(root); }
    void printToFile(std::string fileName) { if(root != NULL) root->printToFile(fileName, root); }
    
    BinaryNode* find(int x, BinaryNode *t);
    BinaryNode* findMin(BinaryNode *t);
    BinaryNode* removeMin(BinaryNode *t);
    int findHeight(int x, BinaryNode *t);
    BinaryNode* insert(int x, BinaryNode *t, int count);
    BinaryNode* setRoot(int x);
    BinaryNode* remove(int x, BinaryNode *t);
    BinaryNode* search(int searchKey);
    void updateSearchCost(BinaryNode *t);
    int totalSearchCost(int totalCost, BinaryNode *t) { return (root==NULL) ? 0 : root->totalSearchCost(root); }
    int averageSearchCost(BinaryNode *t);
};