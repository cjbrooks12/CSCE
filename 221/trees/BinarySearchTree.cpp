#include "BinarySearchTree.h"

BinaryNode* BinarySearchTree::setRoot(int x) {
    root = new BinaryNode(x);
    root->searchCost = 1;
}

BinaryNode *BinarySearchTree::insert(int x, BinaryNode *t, int count) {
    if (t == NULL) {
        t = new BinaryNode(x);
        t->searchCost = count;
    }
    else if (x < t->key) {
        count++;
        t->left = insert(x, t->left, count);
    }
    else if (x > t->key) {
        count++;
        t->right = insert(x, t->right, count);
    }
    else return NULL;
    return t;
}

BinaryNode *BinarySearchTree::findMin(BinaryNode *t) {
    if (t == NULL) {}
    while (t->left != NULL) t = t->left;
    return t;
}

BinaryNode *BinarySearchTree::removeMin(BinaryNode *t) {
    if (t == NULL) {}
    if (t->left != NULL) {
        t->left = removeMin(t->left);
    }
    else {
        BinaryNode *node = t;
        t = t->right;
        delete node;
    }
    return t;
}

BinaryNode *BinarySearchTree::find(int x, BinaryNode *t) {
    while (t != NULL) {
        if (x < t->key) {
            t = t->left;
        }
        else if (x > t->key) {
            t = t->right;
        }
        else {
            return t;
        }
    }
}

int BinarySearchTree::findHeight(int x, BinaryNode *t) {
    int count = 0;
    while (t != NULL) {
        if (x < t->key) {
            count++;
            t = t->left;
        }
        else if (x > t->key) {
            count++;
            t = t->right;
        }
        else {
            return count;
        }
    }
}

//updates the search costs for all nodes by using an inorder traveral to find the height of each node, which is the searchCost
void BinarySearchTree::updateSearchCost(BinaryNode *t) { 
    if (t->left != NULL) updateSearchCost(t->left);
    
    t->searchCost = findHeight(t->key, root);
    
    if (t->right != NULL) updateSearchCost(t->right);  
}


BinaryNode *BinarySearchTree::remove(int x, BinaryNode *t) { 
    if (t == NULL) {} 
    if (x < t->key) {
        t->left = remove(x, t->left);
    }
    else if (x > t->key) {
        t->right = remove(x, t->right);
    }
    else if (t->left != NULL && t->right != NULL) {
        // item x is found; t has two children
        t->key = findMin(t->right)->key;
        t->right = removeMin(t->right);
    } 
    else { //t has only one child
        BinaryNode *node = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete node;
    }
    
    updateSearchCost(root);
    
    return t;
}

int BinarySearchTree::averageSearchCost(BinaryNode *t) {
    int cost = totalSearchCost(0, t);
    int numberElements = size();
    
    return cost / numberElements;
}



















