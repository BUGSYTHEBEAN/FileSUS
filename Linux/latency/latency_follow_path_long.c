#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BASE_DIR "../../../../.."
#define DIR_ONE "test/"
#define DIR_TWO "next/"
#define DIR_THREE "then/"
#define DIR_FOUR "again/"
#define DIR_FIVE "last/"
#define FULL_DIR DIR_ONE DIR_TWO DIR_THREE DIR_FOUR DIR_FIVE

int main(int argc, char *argv[]) {
    if (access(FULL_DIR, F_OK)) {
        rmdir(DIR_ONE);
        if (mkdir(DIR_ONE, 0777) == -1) {
            printf("Error making directory 1\n");
            exit(1);
        }
        if (mkdir(DIR_ONE DIR_TWO, 0777) == -1) {
            printf("Error making directory 2\n");
            exit(1);
        }
        if (mkdir(DIR_ONE DIR_TWO DIR_THREE, 0777) == -1) {
            printf("Error making directory 3\n");
            exit(1);
        }
        if (mkdir(DIR_ONE DIR_TWO DIR_THREE DIR_FOUR, 0777) == -1) {
            printf("Error making directory 4\n");
            exit(1);
        }
        if (mkdir(DIR_ONE DIR_TWO DIR_THREE DIR_FOUR DIR_FIVE, 0777) == -1) {
            printf("Error making directory 5\n");
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
        if (chdir(FULL_DIR) != 0) {
            perror("cd failed");
            exit(1);
        }
        
        if (clock_gettime(CLOCK_REALTIME, &stop) == -1) {
            perror("Stopping the clock failed");
        }
        // Go back up
        if (chdir(BASE_DIR) != 0) {
            perror("cd back failed");
            exit(1);
        }
        long int current = stop.tv_nsec - start.tv_nsec;
        if (current < min && current > 0) {
            min = current;
            printf("Elapsed time in nanoseconds: %li\n", min);
        }
    }
}