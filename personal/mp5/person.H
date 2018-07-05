#ifndef _person_H_                 
#define _person_H_

#include <string>
#include <iomanip>
#include <pthread.h>

#include "buffer.H"

using namespace std;

class Person {
private:
    int histogram[100];

public:
    string name;
    int id;
    
    BoundedBuffer<int>* stat_buffer;
    pthread_t request_t, stat_t;
    
    Person(string _name, int _id, int buffer_size) {
        name = _name;
        id = _id;
        stat_buffer = new BoundedBuffer<int>(buffer_size);
        
        for(int i = 0; i < 100; i++) {
            histogram[i] = 0;
        }
    }  
    
    ~Person() {
        delete stat_buffer;
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
};

#endif