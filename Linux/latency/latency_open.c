#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define UP_ONE_DIR ".."
#define FILE_NAME "test.txt"

int main(int argc, char *argv[]) {
    FILE* fd = fopen(FILE_NAME, "w");
    fputc(69, fd);
    fclose(fd);

    struct timespec start;
    struct timespec stop;
    long int min = __INT_MAX__;
    
    char buf[1];

    for (;;) {
        // Start clock
        if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
            perror("Starting the clock failed");
        }
        // Open test file
        FILE* test_file = fopen(FILE_NAME, "r");
        while (test_file == NULL) {
            test_file = fopen(FILE_NAME, "r");
        }
        // Stop clock
        if (clock_gettime(CLOCK_REALTIME, &stop) == -1) {
            perror("Stopping the clock failed");
        }
        // Close test file
        fclose(test_file);
        long int current = stop.tv_nsec - start.tv_nsec;
        if (current < min && current > 0) {
            min = current;
            printf("Elapsed time in nanoseconds: %li\n", min);
        }
    }
}