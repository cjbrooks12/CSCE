#include "BinaryNode.h"
#include <iostream>
#include <fstream>

int BinaryNode::size(BinaryNode *t) {
    if (t == NULL) return 0;
    else return 1 + size(t->left) + size(t->right); 
}


int BinaryNode::totalSearchCost(BinaryNode *t) {
    if (t == NULL) return 0;
    else return t->searchCost + totalSearchCost(t->left) + totalSearchCost(t->right); 
}

int BinaryNode::height(BinaryNode *t) {
    if (t == NULL) {
        return 0;
    }
    else if(size(t) == 1) return 1;
    else {
        int hlf = height(t->left);
        int hrt = height(t->right);
        return (hlf > hrt) ? 1+hlf : 1+hrt; // 1+max(hlf,hrt)
    }
}

void BinaryNode::print(BinaryNode *t) {
    if (t->left != NULL) t->print(t->left);
    std::cout << t->key << "[" << t->searchCost << "]\n";
    if (t->right != NULL) t->print(t->right);    
}

void BinaryNode::printToFile(std::string fileName, BinaryNode *t) {
    std::ofstream ofs;
    ofs.open(fileName, std::ofstream::app);
    
    if (t->left != NULL) t->printToFile(fileName, t->left);
    ofs << t->key << "[" << t->searchCost << "]\n";
    ofs.close();
    if (t->right != NULL) t->printToFile(fileName, t->right);    
}