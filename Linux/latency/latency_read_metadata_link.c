#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define FILE_NAME "test.txt"
#define LINK_NAME "symlink.txt"

int main(int argc, char *argv[]) {
    struct timespec start;
    struct timespec stop;
    long int min = __INT_MAX__;
    struct stat sb;

    if (access(LINK_NAME, F_OK)) {
        if (symlink(FILE_NAME, LINK_NAME) == -1) {
            printf("Error making link\n");
            exit(1);
        }
    }

    for (;;) {
        // Start clock
        if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
            perror("Starting the clock failed");
        }
        // Measure reading link metadata
        while (lstat(LINK_NAME, &sb) != -1) {}
        // Stop clock
        if (clock_gettime(CLOCK_REALTIME, &stop) == -1) {
            perror("Stopping the clock failed");
        }
        long int current = stop.tv_nsec - start.tv_nsec;
        if (current < min && current > 0) {
            min = current;
            printf("Elapsed time in nanoseconds: %li\n", min);
        }
    }
}