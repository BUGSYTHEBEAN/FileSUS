#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define FILE_NAME "test.txt"
#define LINK_NAME "symlink.txt"

int main(int argc, char *argv[]) {
    struct timespec start;
    struct timespec stop;
    long int min = 1000000;
    struct stat sb;
    #define F_OK 0

    for (;;) {
        // Start clock
        if(timespec_get(&start, TIME_UTC) != TIME_UTC){
            exit(1);
            //error
        }
        // Measure reading link metadata
        while (stat(LINK_NAME, &sb) == -1) {}
        // Stop clock
        if(timespec_get(&stop, TIME_UTC) != TIME_UTC){
            exit(1);
            //error
        }
        long int current = stop.tv_nsec - start.tv_nsec;
        if (current < min && current > 0) {
            min = current;
            printf("Elapsed time in nanoseconds: %li\n", min);
        }
    }
}