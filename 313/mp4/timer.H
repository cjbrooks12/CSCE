#include <sys/time.h>
#include <assert.h>

typedef struct timeval timer;


class Timer {
private:
    struct timeval begin;
    struct timeval end;
    struct timeval difference;
    
public:
    Timer() {
        
    }
    
    void start() {
        assert(gettimeofday(&begin, 0) == 0);
        difference.tv_sec = -1;
        difference.tv_usec = -1;
    }
    
    void finish() {
        assert(gettimeofday(&end, 0) == 0);
        difference.tv_sec = end.tv_sec - begin.tv_sec;
        difference.tv_usec = end.tv_usec - begin.tv_usec;
        if (difference.tv_usec < 0) {
            difference.tv_usec += 1000000;
            difference.tv_sec--;
        }
    }
    
    long sec() {
        return difference.tv_sec;
    }
    
    long usec() {
        return difference.tv_usec;
    }
};