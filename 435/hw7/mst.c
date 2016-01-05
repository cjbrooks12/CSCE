//
// Computes the minimum spanning tree (MST) of a weighted graph
// The graph is provided as an adjacency matrix A
//
// Warning: Return values of calls are not checked for error to keep 
// the code simple.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>


enum { FALSE, TRUE };

#define MAX_N 65536
#define MAX_THREADS 1024


//#define INFINITY   	1.0e300

// MST
typedef struct _mst {
    unsigned int n;		// number of nodes in the tree
    unsigned int *node; 	// edge (i,node[i]) is in the MST
    double *weight; 		// weight of edge (i,node[i])
    double mst_weight; 		// weight of MST (sum of weights of all edges
} MST_t; 
// Adjacency matrix structure
typedef struct _adj_matrix {
    double ** weight; 
    int n; 
} ADJ_MATRIX_t;

struct timespec parallel_start, parallel_stop, serial_start, serial_stop;

// Variable Declarations


// -----------------------------------------------------------------------------
// Threading code
int num_threads;
short int *inserted_in_mst;
double *d;
unsigned int u;
double minwt;
ADJ_MATRIX_t *A;        // Adjacency Matrix of graph
MST_t * mst;

pthread_mutex_t lock_minimum;
int thread_id[MAX_THREADS];
pthread_t p_threads[MAX_THREADS];
pthread_attr_t attr;

void* find_min (void *s) {
    int my_thread_id = *((int *)s);

    int block_size = (A->n)/num_threads;
    int my_start = my_thread_id*block_size;
    int my_end = (my_thread_id+1)*block_size-1;
    if (my_thread_id == num_threads-1) my_end = (A->n)-1;

    // printf("find min tid[%d], my_start[%d], my_end[%d]\n", my_thread_id, my_start, my_end);

    for (int i = my_start; i <= my_end; i++) {
        if (!inserted_in_mst[i]) {
            pthread_mutex_lock(&lock_minimum);
            if (d[i] < minwt) {
                u = i; 
                minwt = d[i];
            }
            pthread_mutex_unlock(&lock_minimum);
       }
    }

    return NULL;
}

void* update_d (void *s) {
    int my_thread_id = *((int *)s);

    int block_size = (A->n)/num_threads;
    int my_start = my_thread_id*block_size;
    int my_end = (my_thread_id+1)*block_size-1;
    if (my_thread_id == num_threads-1) my_end = (A->n)-1;

    // printf("update d tid[%d], my_start[%d], my_end[%d]\n", my_thread_id, my_start, my_end);

    for (int i = my_start; i <= my_end; i++) {
        if (!inserted_in_mst[i]) {
            pthread_mutex_lock(&lock_minimum);
            if (d[i] > A->weight[u][i]) {
                d[i] = A->weight[u][i];
                mst->node[i] = u;
                // printf("(tid=%d): d[%d]=%f, u=%d, mst.n=%d, mst.nodes[%d]=%d\n", my_thread_id, i, d[i], u, mst->n, i, mst->node[i]);
            }
            pthread_mutex_unlock(&lock_minimum);
        }
    }


    return NULL;
}

// -----------------------------------------------------------------------------
// MST Routines
//
// Create and initialize MST
//
MST_t * init_mst ( ADJ_MATRIX_t * A ) {
    unsigned i;
    MST_t * mst = calloc(1, sizeof(MST_t));
    mst->n = A->n;
    mst->node = calloc(mst->n, sizeof(unsigned int)); 
    mst->weight = calloc(mst->n, sizeof(double)); 
    for (i = 0; i < mst->n; i++) {
        mst->node[i] = i;
        mst->weight[i] = 0.0;
    }
    mst->mst_weight = 0.0; 
    return mst;
}
// -----------------------------------------------------------------------------
// Adjacency Matrix Routines
//
// Create and initialize adjacency matrix A with edge weights of the graph
//   A->n denotes size of matrix
//   A->weight[i][j] denotes weight edge from nodes i and j
//
ADJ_MATRIX_t* init_adj_matrix ( unsigned int num_nodes, unsigned int seed ) {
    unsigned int i, j;
    ADJ_MATRIX_t * A = calloc(1, sizeof(ADJ_MATRIX_t));
    A->n = num_nodes;
    // Allocate storage for matrix elements
    A->weight = calloc(A->n, sizeof(double *));
    for (i = 0; i < A->n; i++) {
        A->weight[i] = calloc(A->n, sizeof(double));
    }
    // Initialize matrix elements
    srand(seed); 
    double randwt;
    for (i = 0; i < A->n; i++) {
        for (j = i; j < A->n; j++) {
            if (i == j) {
                A->weight[i][j] = 0.0;
            } 
            else {
                // Insert random edge weights
                A->weight[i][j] = (double)(rand_r(&seed))/(double)(RAND_MAX);
                A->weight[j][i] = A->weight[i][j];
            }
        }
    }
    return A;
}

void parallel_minimum_spanning_tree(ADJ_MATRIX_t * A, unsigned int root) {
    unsigned int i, j, nodes;

    // Initialize MST
    mst = init_mst(A);

    // Initialize weight vector d with weight of edges connecting node i to root
    d = calloc(A->n, sizeof(double)); 
    for (i = 0; i < A->n; i++) {
        d[i] = A->weight[root][i];  // d[i]= min wt. edge from node i to MST
        mst->node[i] = root;        // closest MST node to node i 
    }
    // Initialize flag that indicates whether a node has been inserted in the tree
    inserted_in_mst = calloc(A->n, sizeof(short int)); 
    for (i = 0; i < A->n; i++) {
        inserted_in_mst[i] = FALSE;
    }

    // Prim's MST algorithm

    // Insert root into MST
    inserted_in_mst[root] = TRUE;
    mst->node[root] = root;
    mst->weight[root] = 0.0;
    mst->mst_weight = 0.0;

    nodes = 1; 
    while (nodes < A->n) {
        // Find node u not belonging to MST with minimum weight edge in d
        minwt = INFINITY;

        //PARALLELIZE HERE
        //  create threads
        //  assign ids to each thread
        //  each thread searches own columns. columns are calculated from ids
        //  reduce local mins from each thread
        //  join threads to main thread
        //  continue algorithm

        // printf("nodes=%d. Starting %d threads to find min\n", nodes, num_threads);
        for (int i = 0; i < num_threads; i++) {
            thread_id[i] = i; 
            pthread_create(&p_threads[i], &attr, find_min, (void *) &thread_id[i]); 
        }
        // printf("nodes=%d. joining %d threads that are finding min\n", nodes, num_threads);
        for (int i = 0; i < num_threads; i++) {
            pthread_join(p_threads[i], NULL);
        }
        // printf("nodes=%d. min found at node %d with weight %f\n", nodes, u, d[u]);


        pthread_mutex_lock(&lock_minimum);

        // Add u to MST
        inserted_in_mst[u] = TRUE;
        mst->weight[u] = d[u];
        mst->mst_weight += d[u];
        nodes++;

        pthread_mutex_unlock(&lock_minimum);

        // Update d vector

        //PARALLELIZE HERE
        //  create threads
        //  assign ids to each thread
        //  each thread searches own columns. columns are calculated from ids
        //  each thread updates weights of d
        // printf("nodes=%d. Starting %d threads to update d vector\n", (nodes-1), num_threads);
        for (int i = 0; i < num_threads; i++) {
            thread_id[i] = i; 
            pthread_create(&p_threads[i], &attr, update_d, (void *) &thread_id[i]); 
        }
        // printf("nodes=%d. joining %d threads that are updating d vector\n", nodes, num_threads);
        for (int i = 0; i < num_threads; i++) {
            pthread_join(p_threads[i], NULL);
        }
        // printf("nodes=%d. done updating d. Total MST weight is now %f\n", (nodes-1), mst->mst_weight);

    }
}

// Compute minimum spanning tree of graph A
MST_t* serial_minimum_spanning_tree(ADJ_MATRIX_t * A, unsigned int root) {
    unsigned int i, j, u, nodes;
    double minwt; 

    // Initialize MST
    MST_t * mst = init_mst(A);

    // Initialize weight vector d with weight of edges connecting node i to root
    double * d = calloc(A->n, sizeof(double)); 
    for (i = 0; i < A->n; i++) {
        d[i] = A->weight[root][i];	// d[i]= min wt. edge from node i to MST
        mst->node[i] = root;		// closest MST node to node i 
    }
    // Initialize flag that indicates whether a node has been inserted in the tree
    short int * inserted_in_mst = calloc(A->n, sizeof(short int)); 
    for (i = 0; i < A->n; i++) {
        inserted_in_mst[i] = FALSE;
    }

    // Prim's MST algorithm

    // Insert root into MST
    inserted_in_mst[root] = TRUE;
    mst->node[root] = root;
    mst->weight[root] = 0.0;
    mst->mst_weight = 0.0;

    nodes = 1; 
    while (nodes < A->n) {
        // Find node u not belonging to MST with minimum weight edge in d
        minwt = INFINITY;
        for (i = 0; i < A->n; i++) {
            if ((!inserted_in_mst[i]) && (d[i] < minwt)) {
                u = i; 
                minwt = d[i];
           }
        }
        // Add u to MST
        inserted_in_mst[u] = TRUE;
        mst->weight[u] = d[u];
        mst->mst_weight += d[u];
        nodes ++;

        // Update d vector
        for (i = 0; i < A->n; i++) {
            if ((!inserted_in_mst[i]) && (d[i] > A->weight[u][i])) {
                d[i] = A->weight[u][i];
                mst->node[i] = u;	// set u as closest MST node of i
            }
        }
    }
    return mst; 
}
// Main program 
// - Initialize adjacency matrix A of a graph
// - Computes minimum spanning tree with a given starting node
int main(int argc, char *argv[]) {

    unsigned int num_nodes, root, seed;

    if (argc != 4) {
        printf("Use: <executable_name> <num_nodes> <root_node> <seed>\n"); 
        exit(0);
    }
    if ((num_nodes = atoi(argv[argc-3])) > MAX_N) {
        printf("Maximum number of nodes allowed: %d\n", MAX_N);
        exit(0);
    }; 
    if ((root = atoi(argv[argc-2])) > num_nodes-1) {
        printf("Root node (%d) should be in the range [0,...,%d]\n", root, num_nodes-1);
        exit(0);
    };
    seed = atoi(argv[argc-1]);

    // Initialize adjacency matrix of graph
    A = init_adj_matrix(num_nodes, seed);

    // Initialize mutex and attribute structures
    pthread_mutex_init(&lock_minimum, NULL); 
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    num_threads = (num_nodes >= 20) ? 20 : num_nodes;

    //run parallel MST algorithm to get parallel time
    clock_gettime(CLOCK_REALTIME, &parallel_start);
    parallel_minimum_spanning_tree(A, root); 
    clock_gettime(CLOCK_REALTIME, &parallel_stop);
    
    float parallel_time =
        (parallel_stop.tv_sec - parallel_start.tv_sec) + 
        0.000000001 * (parallel_stop.tv_nsec - parallel_start.tv_nsec);
    printf("MST (parallel): Nodes=%d, MST Weight=%f time=%fns\n", A->n, mst->mst_weight, parallel_time); 

    //run serial code to get serial time
    clock_gettime(CLOCK_REALTIME, &serial_start);
    MST_t* mst_serial = serial_minimum_spanning_tree(A, root); 
    clock_gettime(CLOCK_REALTIME, &serial_stop);
    
    float serial_time = 
        (serial_stop.tv_sec - serial_start.tv_sec) + 
        0.000000001 * (serial_stop.tv_nsec - serial_start.tv_nsec);
    printf("MST (serial): Nodes=%d, MST Weight=%f, time=%fms\n", A->n, mst_serial->mst_weight, serial_time); 
}





















