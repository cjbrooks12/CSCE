#include <cstddef> //to define NULL
#include <string>

class BinaryNode {
private:
    int key, searchCost;
    BinaryNode *left, *right;
    friend class BinarySearchTree;
    
public:
    
    BinaryNode(int mKey)
        : key(mKey), left(NULL), right(NULL) { }
    BinaryNode(int mKey, BinaryNode *mLeft, BinaryNode *mRight)
        : key(mKey), left(mLeft), right(mRight) { }
    
    BinaryNode* getLeft() { return left; }
    BinaryNode* getRight() { return right; }
    int getKey() { return key; }
    int getSearchCost() {return searchCost; }
    void setSearchCost(int i) { searchCost = i; }
               
    int size(BinaryNode *t);
    int height(BinaryNode *t);
    int totalSearchCost(BinaryNode *t);
    void print(BinaryNode *t);
    void printToFile(std::string fileName, BinaryNode *t);
};