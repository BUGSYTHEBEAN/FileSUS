#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define FILE_NAME "test.txt"

int main(int argc, char *argv[]) {
    struct timespec start;
    struct timespec stop;
    long int min = 1000000;
    
    for (;;) {
        if (chmod(FILE_NAME, 666) != 0) {
            printf("Error changing permissions\n");
            exit(1);
        }
        // Start clock
        if(timespec_get(&start, TIME_UTC) != TIME_UTC){
            exit(1);
            //error
        }
        // Measure changing file permissions
        if (chmod(FILE_NAME, 664) != 0) {
            printf("Error changing permissions measured\n");
            exit(1);
        }
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