/**
\file BinaryHeap.h
\author Eduard Igushev visit <www.igushev.com> e-mail: <first name at last name dot com>
\brief Binary Heap C++ implementation

Warranty and license
The implementation is provided “as it is” with no warranty.
Any private and commercial usage is allowed.
Keeping the link to the source is required.
Any feedback is welcomed :-)
*/

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <cmath>
#include "Edge.h"

//------------------------------------------------------------------------------
template <class T>
class PriorityQueue {
private:
    vector<Locator<T>* > keys;
    
	void shiftDown(int node) {
        int leftChild = node * 2 + 1;
        int rightChild = node * 2 + 2;
        int replace = node;
		
		counter++;
        
        if (rightChild < keys.size()) { 
            bool left = keys[leftChild] < keys[rightChild];
            
            if (left && keys[leftChild] < keys[node]) {
                replace = leftChild;
            }
            else if (!left && keys[rightChild] < keys[node]) {
                replace = rightChild;
            }
        }
        else if (leftChild < keys.size()) { 
            if (keys[leftChild] < keys[node]) {
                replace = leftChild;
            }
        }
    
        if (replace == node) return;
        
        swap(keys[node], keys[replace]);
        
        shiftDown(replace);
    }
    
	void shiftUp(int node) {
		counter++;
        if (node == 0) return;

        int parent = floor((node - 1) / 2);

        if (keys[parent] < keys[node]) return;
        
        swap(keys[node], keys[parent]);
        
        shiftUp(parent);
    }

public:
	PriorityQueue() {}
	~PriorityQueue() {}
    
    void buildHeap() {
        for (int i = keys.size() / 2; i >= 0; --i) {
           shiftDown(i);
        }
    }

	void insert(int dist, Locator<T>* value) {
        value->key = dist;
        keys.push_back(value);
        shiftUp(keys.size() - 1);
    }
    
    void updateKey(Locator<T>* value, int newKey){
        value->key = newKey;
        buildHeap();
    }
    
	Locator<T>* removeMin() {
        Locator<T>* result = keys.front();
        keys.front() = keys.back();
        keys.pop_back();
        shiftDown(0);
        return result;
    }
    
	int count() const { return keys.size(); }
    
    friend ostream& operator<<(ostream& ost, const PriorityQueue<T>& pq) {
        for(int i = 0; i < pq.keys.size(); ++i) {
            ost << pq.keys[i]->key << endl;   
        }
        
        return ost;
    }
};

#endif