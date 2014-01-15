#ifndef GRAPH_H
#define GRAPH_H

#include "PriorityQueue.h"

template<typename T>
class Graph{

private:
	vector<Vertex<T>*> vertList;
	vector<Edge<T>*> edgeList;
    
public:
//Constructors and initialization
//------------------------------------------------------------------------------
    Graph<T>() { }
    
	Graph<T>(string filename) {
		ifstream ifs(filename.c_str());
		int vertnum; //number of vertices in the graph
		ifs>>vertnum;
        //push all vertices into the vertex vector before assigning the in and out list
		for(int i=0;i<vertnum;i++) {
			Vertex<T> *vert = new Vertex<T>(i+1);
			vertList.push_back(vert);
		}
		int src,dest,weight; 
		ifs>>src; 
		while(src!=-1) {
			ifs>>dest; 
			while(dest!=-1) {
				ifs>>weight; // one weight means one edge
                Edge<T> *tempedge = new Edge<T>(vertList[src-1],vertList[dest-1],weight); // new edge
				edgeList.push_back(tempedge);				
				vertList[src-1]->outList.push_back(tempedge);
				vertList[dest-1]->inList.push_back(tempedge);
				ifs>>dest; 
			}
			ifs>>src; 
		}
		ifs.close();
	}
	
    ~Graph() {
		for(auto i = 0; i < vertList.size(); i++)
			delete vertList[i];
		for(auto i = 0; i < edgeList.size(); i++)
			delete edgeList[i];
	}

//Public setters
//------------------------------------------------------------------------------
    
    //adds new vertex without any associated edges, given a Vertex object
    Locator<T>* addVertex(Vertex<T>* v) { 
        vertList.push_back(v);
        return v->getLocator();
    }
    
    //adds new vertex without any associated edges, given a item of type T
    Locator<T>* addVertex(T item) { 
        Vertex<T>* v = new Vertex<T>(item);
        vertList.push_back(v); 
        return v->getLocator();
    }
    
    //Given two existing vertices, create an edge between them
    void addEdge(Vertex<T>* src, Vertex<T>* dest, int weight) {
        Edge<T>* edge = new Edge<T>(src, dest, weight);
        src->addOutEdge(edge);
        dest->addInEdge(edge);
        
        edgeList.push_back(edge);
    }
    
//Public Getters
//------------------------------------------------------------------------------
    vector<Vertex<T>*> getVertices() const { return vertList; }
    vector<Edge<T>*> getEdges() const { return edgeList; } 
    vector<Locator<T>*> getLocators() const {
        vector<Locator<T>*> locList;
        for(auto i = 0; i < vertList.size(); ++i) {
            locList.push_back(vertList[i]->getLocator());
        }
		return locList;
	} 
    
//Algorithms
//------------------------------------------------------------------------------    
    vector<Locator<T>*> dijkstra(Vertex<T>* source) {
        int INF = 100000;
        vector<Locator<T>*> cloud;
        PriorityQueue<T> vertices;
        
        source->getLocator()->path.push_back(source);
        
        for(int i = 0; i < vertList.size(); ++i) {
            vertices.insert(INF, vertList[i]->getLocator());
        }
        
        vertices.updateKey(source->getLocator(), 0);
        
        
        while(vertices.count() > 0) {
            //get the vertex that the min in the PQ has the shortest edge to
            Locator<T>* loc = vertices.removeMin();
            cloud.push_back(loc);
			counter++;
            
            //relax edges of min vertex
            vector<Edge<T>*> edges = loc->v->getOutEdges();
            for(int i = 0; i < edges.size(); ++i) {
				counter++;
                Locator<T>* destLocator = edges[i]->getDestinationVertex()->getLocator();
                int weight = edges[i]->getWeight();
                if((loc->key + weight) < destLocator->key) {
                    vertices.updateKey(destLocator, (loc->key + weight));
                    destLocator->path.clear();
                    destLocator->path.push_back(loc->v);
                }
            }            
        }
        return cloud;        
    }
    
    vector<Edge<T>*> shortestPathBetween(Vertex<T>* begin, Vertex<T>* end) {
        dijkstra(begin);
        
        vector<Edge<T>*> shortestPath;
        Locator<T>* loc = end->getLocator();
        
        while(loc->path[0] != loc->v) {
            for(int j = 0; j < loc->v->getInEdges().size(); ++j) {
			counter++;
                if(loc->v->getInEdges()[j]->getSourceVertex() == loc->path[0]) {
                    shortestPath.push_back(loc->v->getInEdges()[j]);
                }   
            }
            loc = loc->path[0]->getLocator();
        }
        return shortestPath;
    }

//Operators
//------------------------------------------------------------------------------
    void printToFile(string filename) {
        ofstream outputFile;
        outputFile.open(filename);
        outputFile << *this;
        outputFile.close();
    }
        
    friend std::ostream& operator<<(std::ostream& ost, const Graph<T>& g) {        
        for(int i = 0; i < g.vertList.size(); ++i) {
            ost << *g.vertList[i] << endl;
        }
        return ost;
    }
//------------------------------------------------------------------------------ 
};
#endif