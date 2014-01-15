#include "Graph.h"

//Test large graph with given input of ints from text file
void testInt() {
    Graph<int> g("new.txt");
    vector<Locator<int>*> intLocators = g.getLocators();
    
    int vertexCount = g.getVertices().size();
    
    cout << "do you want to view the entire graph or run dijkstra's algorithm?" << endl <<
        "[-F 'filename'] to output graph to file" << endl << 
        "[-D 'source index'] to run dijkstra's algorithm starting at the index of the vertex given. " 
        "This number must be between 0 and " << vertexCount - 1 << endl <<
        "[-B 'source index' 'end index'] to get the shortest path between two vertices" <<  endl <<
        "The numbers must be between 0 and " << vertexCount - 1 << endl;
    
    string choice, input;
    cin >> choice >> input;
    
    if(choice == "-F") cout << g;//g.printToFile(input);
    else if(choice == "-D") {
        vector<Locator<int>*> cloud = g.dijkstra(intLocators[atoi(input.c_str())]->v);
        
        for(int i = 0; i < cloud.size(); ++i) {
            cout << cloud[i]->v->getItem() << ": " << cloud[i]->key << "[";
                for(int j = 0; j < cloud[i]->path.size(); ++j) {
                    cout << cloud[i]->path[j]->getItem();
                }
            cout << "]" << endl;
        }
    }
    else if(choice == "-B") {
        int end, totalPathLength = 0;
        cin >> end;
        vector<Edge<int>*> path = g.shortestPathBetween(intLocators[atoi(input.c_str())]->v, intLocators[end]->v);
        cout << "[" << intLocators[atoi(input.c_str())]->v->getItem() << "]";
        for(int t = (path.size() - 1); t >= 0; t--) {
            totalPathLength += path[t]->getWeight();
            cout << *path[t];
        }
        cout << endl << "total path length: " << totalPathLength << endl;
		cout << counter << " total comparisons" << endl;
    }
    else cout << "invalid selection" << endl;
}

//Test small graph with string input added manually and edges connected using locators
void testString() {
    Graph<string> gg;
    vector<Locator<string>*> locators;
    
    locators.push_back(gg.addVertex("a"));
    locators.push_back(gg.addVertex("b"));
    locators.push_back(gg.addVertex("c"));
    locators.push_back(gg.addVertex("d"));
    locators.push_back(gg.addVertex("e"));
    locators.push_back(gg.addVertex("f"));
 
    gg.addEdge(locators[0]->v, locators[1]->v, 2);  
    gg.addEdge(locators[0]->v, locators[3]->v, 1); 
    gg.addEdge(locators[0]->v, locators[4]->v, 2); 
    gg.addEdge(locators[1]->v, locators[2]->v, 4); 
    gg.addEdge(locators[1]->v, locators[5]->v, 6); 
    gg.addEdge(locators[3]->v, locators[2]->v, 2); 
    gg.addEdge(locators[3]->v, locators[4]->v, 3); 
    gg.addEdge(locators[2]->v, locators[5]->v, 9);
    gg.addEdge(locators[4]->v, locators[5]->v, 7);
    gg.addEdge(locators[5]->v, locators[3]->v, 3);
    
    int vertexCount = gg.getVertices().size();
    
    cout << "do you want to view the entire graph or run dijkstra's algorithm?" << endl <<
        "[-F 'filename'] to output graph to file" << endl << 
        "[-D 'source index'] to run dijkstra's algorithm starting at the index of the vertex given. " 
        "This number must be between 0 and " << vertexCount - 1 << endl <<
        "[-B 'source index' 'end index'] to get the shortest path between two vertices" <<  endl <<
        "The numbers must be between 0 and " << vertexCount - 1 << endl;
    
    string choice, input;
    cin >> choice >> input;
    
    if(choice == "-F") gg.printToFile(input);
    else if(choice == "-D") {
        vector<Locator<string>*> cloud = gg.dijkstra(locators[atoi(input.c_str())]->v);
        
        for(int i = 0; i < cloud.size(); ++i) {
            cout << cloud[i]->v->getItem() << ": " << cloud[i]->key << "[";
                for(int j = 0; j < cloud[i]->path.size(); ++j) {
                    cout << cloud[i]->path[j]->getItem();
                }
            cout << "]" << endl;
        }
    }
    else if(choice == "-B") {
        int end, totalPathLength = 0;
        cin >> end;
        vector<Edge<string>*> path = gg.shortestPathBetween(locators[atoi(input.c_str())]->v, locators[end]->v);
        cout << "[" << locators[atoi(input.c_str())]->v->getItem() << "]";
        for(int t = (path.size() - 1); t >= 0; t--) {
            totalPathLength += path[t]->getWeight();
            cout << *path[t];
        }
        cout << endl << "total path length: " << totalPathLength << endl;
    }
    else cout << "invalid selection" << endl;    
}

int main() {
    cout << "Do you want to test a graph of ints or strings?" << endl << 
        "type [INT] for integers from file" << endl << 
        "type [STRING] for strings input manually" << endl;
    
    string choice;
    cin >> choice;
    
    for(int i = 0; i < choice.length(); ++i) {
        choice[i] = toupper(choice[i]);
    }
    
    if(choice == "INT") testInt();
    else if(choice == "STRING") testString();
    else cout << "invalid selection" << endl;
    
    return 0;
}

/* References
1) http://www.geeksforgeeks.org/greedy-algorithms-set-7-dijkstras-algorithm-for-adjacency-list-representation/
2) http://www.cprogramming.com/tutorial/computersciencetheory/dijkstra.html

*/
