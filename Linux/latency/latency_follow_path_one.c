#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UP_ONE_DIR ".."
#define DIR_NAME "test"

int main(int argc, char *argv[]) {
    if (access(DIR_NAME, F_OK)) {
        if (mkdir(DIR_NAME, 0777) == -1) {
            printf("Error making directory\n");
            exit(1);
        }
    }
    struct timespec start;
    struct timespec stop;
    long int min = __INT_MAX__;
    
    for (;;) {
        // Start clock
        if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
            perror("Starting the clock failed");
        }
        // Change directory to newly created one
        if (chdir(DIR_NAME) != 0) {
            perror("cd failed");
            exit(1);
        }
        
        if (clock_gettime(CLOCK_REALTIME, &stop) == -1) {
            perror("Stopping the clock failed");
        }
        // Go back up
        if (chdir(UP_ONE_DIR) != 0) {
            perror("cd failed");
            exit(1);
        }
        long int current = stop.tv_nsec - start.tv_nsec;
        if (current < min && current > 0) {
            min = current;
            printf("Elapsed time in nanoseconds: %li\n", min);
        }
    }
}