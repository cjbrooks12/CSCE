#ifndef _person_H_                 
#define _person_H_

#include <string>
#include <iomanip>

#include "reqchannel.H"

using namespace std;

class Person {
private:
    string name;
    int id;
    int histogram[100];

public:
    Person(string _name, int _id) {
        name = _name;
        id = _id;
        
        for(int i = 0; i < 100; i++) {
            histogram[i] = 0;
        }
    }  
    
    ~Person() {
        
    }
    
    void addToHistogram(int value) {
        histogram[value]++;
    }
    
    void printHistogram() {
        int itemCount = 0;
        for(int i = 0; i < 100; i++) {
            itemCount += histogram[i];
        }
        
        cout << "--------------------------------------------------------------------------------\n";
        cout << name << " Histogram: " << itemCount << " items\n";
        cout << "--------------------------------------------------------------------------------\n";
        cout << "--------------------------------------------------------------------------------\n";
        
        for(int i = 0; i < 100; i++) {
            cout << "[" << setw(2) << i << "] " << setw(4) << histogram[i] << "|";

            for(int j = 0; j < histogram[i]; j++) {
                cout << "*";
            }
            cout << endl;
        }
    }
    
    string getName() {
        return name;
    }
    
    int getId() {
        return id;
    }
};

#endif