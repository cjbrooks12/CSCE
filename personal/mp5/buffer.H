#ifndef _buff_H_                 
#define _buff_H_

#include <vector>

#include "semaphore.H"
using namespace std;

template <typename T> class BoundedBuffer {
private:
    vector<T> buffer;
    int in, out;
    int size;
    int count;
    
    Semaphore empty_sem, full_sem;
    Semaphore mutex;

public:
    BoundedBuffer(int _size) {
        size = _size;
        in = 0; 
        out = 0;
        buffer.resize(size);
        
        empty_sem.init(size);
        full_sem.init(0);
        mutex.init(1);
    }
    
    ~BoundedBuffer() {
        
    }
    
    void deposit(T item) {
        empty_sem.P(); //if no empty spaces, wait      
        mutex.P();   //get exclusive access, make it thread-safe

        buffer[in] = item;
        in = (in+1) % size; 
        count++;
        
        mutex.V(); //release mutex
        full_sem.V(); //increment number of items in buffer
    }
    
    T withdraw() {
        full_sem.P(); //if no items in buffer, wait
        mutex.P(); 
        
        T item = buffer[out];
        out = (out+1) % size; 
        count--;

        mutex.V(); 
        empty_sem.V(); //increment number of empty spaces
        return item;
    }
};

#endif