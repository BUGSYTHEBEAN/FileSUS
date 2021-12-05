#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define FILE_NAME "test.txt"
#define ONE_MEGABYTE 1000000
#define ONE_SECOND 1000000000
#define SECONDS 1800

int main(int argc, char *argv[]) {
    struct timespec start;
    struct timespec stop;
    long int max = 0;
    
    for (;;) {
        int bytes_written = 0;
        time_t elapsed_time = 0;
        // Open test file
        FILE* test_file = fopen(FILE_NAME, "a");
        while (elapsed_time < (ONE_SECOND * SECONDS)) {
            // Start clock
            if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
                perror("Starting the clock failed");
            }
            // Measure write a byte to the file
            while (fputc(69, test_file) != 69) {}
            // Stop clock
            if (clock_gettime(CLOCK_REALTIME, &stop) == -1) {
                perror("Stopping the clock failed");
            }
            bytes_written++;
            elapsed_time += stop.tv_nsec - start.tv_nsec
        }
        // Close test file
        fclose(test_file);
        if (bytes_written > max) {
            max = bytes_written;
            long double elapsed_time_seconds = (long double) elapsed_time / (long double) ONE_SECOND;
            long double measured_data = (long double) max / (long double) ONE_MEGABYTE;
            printf("Measured throughput in MB/s: %lf\n", measured_data / elapsed_time_seconds);
        }
    }
}