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
#define SECONDS 5

int main(int argc, char *argv[]) {
    struct timespec start;
    struct timespec stop;
    long int max = 0;
    
    for (;;) {
        int bytes_read = 0;
        time_t elapsed_time = 0;
        // Open test file
        FILE* test_file = fopen(FILE_NAME, "r");
        fseek(test_file, 0L, SEEK_END);
        size_t size = ftell(fp);
        rewind(test_file);
        while (elapsed_time < (ONE_SECOND * SECONDS)) {
            int random_pos = rand() % size;
            fseek(test_file, random_pos, SEEK_SET);
            // Start clock
            if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
                perror("Starting the clock failed");
            }
            // Measure reading a byte from the file
            while (fread(buf, 1, 1, test_file) != 1) {}
            // Stop clock
            if (clock_gettime(CLOCK_REALTIME, &stop) == -1) {
                perror("Stopping the clock failed");
            }
            bytes_read++;
            elapsed_time += stop.tv_nsec - start.tv_nsec
            if (test_file == EOF || bytes_read >= size) {
                break;
            }
        }
        // Close test file
        fclose(test_file);
        if (bytes_read > max) {
            max = bytes_read;
            long double elapsed_time_seconds = (long double) elapsed_time / (long double) ONE_SECOND;
            long double measured_data = (long double) max / (long double) ONE_MEGABYTE;
            printf("Measured throughput in MB/s: %lf\n", measured_data / elapsed_time_seconds);
        }
    }
}