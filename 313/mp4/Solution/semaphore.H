#ifndef _semaphore_H_                 
#define _semaphore_H_

#include <pthread.h>
#include <semaphore.h>

class Semaphore {
private:
    pthread_mutex_t m;
    pthread_cond_t  c;
    int value;

public:
    Semaphore() {
        
    }
    
    ~Semaphore() {
        
    }
    
    void init(int _val) {
        pthread_mutex_init(&m, NULL);
        pthread_cond_init(&c, NULL);
        value = _val;
    }
    
    void P() {
        pthread_mutex_lock(&m);
        while(value <= 0) {
            pthread_cond_wait(&c, &m);
        }
        value--;
        pthread_mutex_unlock(&m);
    }

    void V() {
        pthread_mutex_lock(&m);
        value++;
        pthread_mutex_unlock(&m);
            pthread_cond_signal(&c);
    }
};

#endif