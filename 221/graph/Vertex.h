#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>
#include <climits>

using namespace std;

template<typename T> class Edge;
template<typename T> class Graph;
template<typename T> class Vertex;
template<typename T> class PriorityQueue;

int counter = 0;

//Locator class
//------------------------------------------------------------------------------
template<typename T> class Locator {
public:
    //key and parent only used in dijkstras algorithm
    int key;
    vector<Vertex<T>*> path;
	Vertex<T>* v;
	friend class Vertex<T>;
    friend class PriorityQueue<T>;
    
    Locator(int k, Vertex<T>* vertex = NULL) {
        key = k;
        v = vertex;
    }
	~Locator() { };
    
    bool operator<(Locator& i) { return key < i.key; }
};

//Vertex class declaration
//------------------------------------------------------------------------------
template <typename T> class Vertex {
private:
	vector<Edge<T>*> inList; // from source vertices
    vector<Edge<T>*> outList; // to end vertices
    T item;
	friend class Graph<T>;
    Locator<T>* loc;
    

public:
//Constructors
//------------------------------------------------------------------------------
    Vertex() {
        item = T();
        loc = new Locator<T>(0, this);   
    }

    Vertex(T ite) {
        item = ite;
        loc = new Locator<T>(0, this);   
    }

//Public Setters
//------------------------------------------------------------------------------
    void setItem(T i) { item = i; }
    void addInEdge(Edge<T>* in) { inList.push_back(in); }
	void addOutEdge(Edge<T>* out) { outList.push_back(out); }
    
//Public Getters
//------------------------------------------------------------------------------
	T getItem() const { return item; }
	vector<Edge<T>*> getOutEdges() const { return outList; }
	vector<Edge<T>*> getInEdges() const { return inList; }
    Locator<T>* getLocator() const { return loc; }
    
    Edge<T>* getShortestEdge() {
        Edge<T>* shortestEdge = outList[0]; 
        int leastWeight = shortestEdge->getWeight();
        for(int i = 0; i < outList.size(); ++i) {
			counter++;
            if(outList[i]->getWeight() < leastWeight) {
                leastWeight = outList[i]->getWeight();
                shortestEdge = outList[i];
            }
        }
        return shortestEdge;
    }    
    
    void printInEdges() {
        cout << "in edges:" << endl;
        for(int i = 0; i < inList.size(); ++i) {
            cout << "[" << inList[i]->getSourceVertex()->getItem() << "]--" 
                << inList[i]->getWeight() << "-->(" << item << ")" << endl;
        }
        cout << endl;
    }
    
    void printOutEdges() {
        cout << *this;
    }
    
    Edge<T>* isAdjacentTo(Vertex<T>* v) {
        for(int i = 0; i < outList.size(); ++i) {
            if(outList[i]->getDestinationVertex() == v) return outList[i];
        }
        for(int i = 0; i < v->outList.size(); ++i) {
            if(v->outList[i]->getDestinationVertex() == this) return v->outlist[i];
        }
        return NULL;
    }
    
    friend ostream& operator<<(ostream& ost, const Vertex<T>& v) {
        ost << "[" << v.item << "]";
        
        for(int i = 0; i < v.outList.size(); ++i) {
            ost << *v.outList[i];
        }
        return ost;
    }    
};

#endif