//
// Computes the minimum of a list using multiple threads
//
// Warning: Return values of calls are not checked for error to keep 
// the code simple.
//
// Compilation command on ADA ($ sign is the shell prompt):
//  $ module load intel
//  $ icc -o list_statistics.exe list_statistics.c -lpthread -lc
//
// Sample execution and output ($ sign is the shell prompt):
//  $ ./list_minimum.exe 1000000 9
// Threads = 9, minimum = 148, time (sec) =   0.0013
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define MAX_THREADS     65536
#define MAX_LIST_SIZE   268435456

int num_threads;		// Number of threads to create - user input 

int thread_id[MAX_THREADS];	// User defined id for thread
pthread_t p_threads[MAX_THREADS];// Threads
pthread_attr_t attr;		// Thread attributes 

pthread_mutex_t lock_minimum;	// Protects minimum, count
int minimum;			// Minimum value in the list
int count;			// Count of threads that have updated minimum

int list[MAX_LIST_SIZE];	// List of values
int list_size;			// List size

//values needed to implement a barrier so that we can calculate list statistics
pthread_mutex_t lock_barrier;   // Protects count
pthread_cond_t cond_barrier;    // Monitors count
int barrier_count;          // Count of threads that have reached barrier

//values needed to list calculate statistics
float sum;
float sum_2;
float mean;
float stdev;

void reset_barrier()
{
    barrier_count = 0;
}

void barrier_sum()
{
    pthread_mutex_lock(&lock_barrier);
    barrier_count++;
    if(barrier_count == num_threads) {
        //we are the last thread, wake up the others
        reset_barrier();
        mean = sum / num_threads;
        pthread_cond_broadcast(&cond_barrier);
    }
    else {
        //there's more work to do, wait on the condition
        pthread_cond_wait(&cond_barrier, &lock_barrier);
    }
    pthread_mutex_unlock(&lock_barrier);
}

void barrier_sum_2()
{
    pthread_mutex_lock(&lock_barrier);
    barrier_count++;
    if(barrier_count == num_threads) {
        //we are the last thread, wake up the others
        stdev = sqrt(sum_2 / num_threads);
        pthread_cond_broadcast(&cond_barrier);
    }
    else {
        //there's more work to do, wait on the condition
        pthread_cond_wait(&cond_barrier, &lock_barrier);
    }
    pthread_mutex_unlock(&lock_barrier);
}

// Thread routine to compute minimum of sublist assigned to thread; 
// update global value of minimum if necessary
void *find_minimum (void *s) {
    int j;
    int my_thread_id = *((int *)s);

    int block_size = list_size/num_threads;
    int my_start = my_thread_id*block_size;
    int my_end = (my_thread_id+1)*block_size-1;
    if (my_thread_id == num_threads-1) my_end = list_size-1;

    // Thread computes minimum of list[my_start ... my_end]
    int my_minimum = list[my_start]; 
    for (j = my_start+1; j <= my_end; j++) {
    if (my_minimum > list[j]) 
        my_minimum = list[j]; 
    }

    //update minumum value if necessary. Additionally, update the sums while we're already locked
    pthread_mutex_lock(&lock_minimum);
    if (minimum > my_minimum) {
        minimum = my_minimum;
        count++;
    }

    sum = (sum + my_minimum);
    pthread_mutex_unlock(&lock_minimum);

    //wait for everyone to add their partial sums. Last thread in calculates mean
    barrier_sum();

    //calculate this threads deviation from the mean, and sum all these up
    float my_deviation = (my_minimum - mean)*(my_minimum - mean);

    pthread_mutex_lock(&lock_minimum);
    sum_2 = (sum_2 + my_deviation);
    pthread_mutex_unlock(&lock_minimum);

    //wait for everyone to add their partial deviation. Last thread in calculates overall standard deviation
    barrier_sum_2();

    // Thread exits
    pthread_exit(NULL);
}

// Main program - set up list of randon integers and use threads to find
// the minimum value; assign minimum value to global variable called minimum
int main(int argc, char *argv[]) {

    struct timeval start, stop; 
    double total_time;
    int i, j; 
    int true_minimum;

    if (argc != 3) {
	printf("Need two integers as input \n"); 
	printf("Use: <executable_name> <list_size> <num_threads>\n"); 
	exit(0);
    }
    if ((list_size = atoi(argv[argc-2])) > MAX_LIST_SIZE) {
	printf("Maximum list size allowed: %d.\n", MAX_LIST_SIZE);
	exit(0);
    }; 
    if ((num_threads = atoi(argv[argc-1])) > MAX_THREADS) {
	printf("Maximum number of threads allowed: %d.\n", MAX_THREADS);
	exit(0);
    }; 
    if (num_threads > list_size) {
	printf("Number of threads (%d) < list_size (%d) not allowed.\n", num_threads, list_size);
	exit(0);
    }; 

    // Initialize mutex and attribute structures
    pthread_mutex_init(&lock_minimum, NULL); 
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    pthread_mutex_init(&lock_barrier, NULL); 
    pthread_cond_init(&cond_barrier, NULL); 

    // Initialize list, compute minimum to verify result
    srand48(0); 	// seed the random number generator
    int max_item_size = 1000;
    list[0] = lrand48(); 
    true_minimum = list[0];
    minimum = list[0];
    for (j = 1; j < list_size; j++) {
	list[j] = lrand48(); 
	if (true_minimum > list[j]) {
	    true_minimum = list[j];
	}
    }

    // Initialize count
    count = 0;
    mean = 0;
    sum = 0;
    sum_2 = 0;
    stdev = 0;

    // Create threads; each thread executes find_minimum
    gettimeofday(&start, NULL); 
    for (i = 0; i < num_threads; i++) {
	thread_id[i] = i; 
	pthread_create(&p_threads[i], &attr, find_minimum, (void *) &thread_id[i]); 
    }
    // Join threads
    for (i = 0; i < num_threads; i++) {
	pthread_join(p_threads[i], NULL);
    }

    // Compute time taken
    gettimeofday(&stop, NULL); 
    total_time = (stop.tv_sec-start.tv_sec)
	+0.000001*(stop.tv_usec-start.tv_usec);

    // Check answer
    if (true_minimum != minimum) {
	printf("Houston, we have a problem!\n"); 
    }
    // Print time taken
    printf("Threads = %d, minimum = %d, mean = %f, stdev = %f, time (sec) = %8.4f\n", 
	    num_threads, minimum, mean, stdev, total_time);

    // Destroy mutex and attribute structures
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&lock_minimum);

    pthread_mutex_destroy(&lock_barrier);
    pthread_cond_destroy(&cond_barrier);
}

