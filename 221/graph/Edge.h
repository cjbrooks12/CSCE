#include "Vertex.h"

#ifndef EDGE_H
#define EDGE_H

template<typename T> class Edge;

//Edge class declaration
//------------------------------------------------------------------------------
template<typename T>
class Edge {
private:
    Vertex<T> *source; // source vertex pointer
	Vertex<T> *destination;    // end vertex pointer
	int weight;        // weight of this edge

public:
    Edge<T>() {
        source = NULL;
        destination = NULL;
        weight = 0;
    }
    
    Edge<T>(Vertex<T>* src, Vertex<T>* dest, int w) {
        source = src;
        destination = dest;
        weight = w;
    }
        
	int getWeight() { return weight; }
	Vertex<T>* getSourceVertex() { return source; }
	Vertex<T>* getDestinationVertex() { return destination; }
    
    friend ostream& operator<<(ostream& ost, const Edge<T>& e) {
        ost << "--" << e.weight << "-->(" << e.destination->getItem() << ")";
        return ost;
    }
};

#endif