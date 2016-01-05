// Game of Drones
//
// Find the drone in a grid 
//
// *** Lines marked "Do not remove" should be retained in your code ***
//
// Warning: Return values of calls are not checked for error to keep 
// the code simple.
//
// Compilation command on ADA:
//   module load intel
//   icc -o find_drone.exe drone.c -lpthread -lrt
//
// Requires drone.h to be in the same directory
//
// Sample execution and output ($ sign is the shell prompt):
// 
// $ ./find_drone.exe 100 0 100000
// Drone = (14,40), success = 1, time (sec) =   1.5213
// $ ./find_drone.exe 400 0 100000
// Drone = (14,240), success = 1, time (sec) =  24.3714
//
#include <pthread.h>
#include <stdio.h>
#include <time.h>

#include "drone.h"		// Do not remove
struct timespec start, stop; 	// Do not remove
double total_time;		// Do not remove
int gridsize;			// Do not remove

int drone_i, drone_j; 		//Coordinates of drone (to be found)

// -------------------------------------------------------------------------
// Data structures and multithreaded code to find drone in the grid 
// ...
// ...
// ...
// ...
// ...
// ...


// -------------------------------------------------------------------------
// Main program to find drone in a grid
int main(int argc, char *argv[]) {

    if (argc != 4) {
	printf("Need four integers as input \n"); 
	printf("Use: <executable_name> <grid_size> <random_seed> <nanosleep_ntime\n"); 
	exit(0);
    }
    // Initialize grid
    gridsize = abs((int) atoi(argv[argc-3])); 		// Do not remove
    int seed = (int) atoi(argv[argc-2]); 		// Do not remove
    int nanosleep_ntime = abs((int) atoi(argv[argc-1]));	// Do not remove
    initialize_grid(gridsize, seed, nanosleep_ntime); 	// Do not remove
    gridsize = get_gridsize();	 			// Do not remove

    clock_gettime(CLOCK_REALTIME, &start); 	// Do not remove

    // Multithreaded code to find drone in the grid 
    // ...
    // ...
    // ... sample serial code shown below ...
    int i, j;
    for (i = 0; i < gridsize; i++) {
	for (j = 0; j < gridsize; j++) {
	    if (check_grid(i,j) == 0) {
		drone_i = i; 
		drone_j = j; 
	    }
	}
    }
    // ...
    // ...
    // ...

    // Compute time taken
    clock_gettime(CLOCK_REALTIME, &stop);			// Do not remove
    total_time = (stop.tv_sec-start.tv_sec)			// Do not remove
	+0.000000001*(stop.tv_nsec-start.tv_nsec);		// Do not remove

    // Check if drone found, print time taken		
    printf("Drone = (%d,%d), success = %d, time (sec) = %8.4f\n", // Do not remove
	    drone_i, drone_j, check_drone_location(drone_i,drone_j), total_time);// Do not remove

    // Other code to wrap up things
    // ...
    // ...
    // ...

}

