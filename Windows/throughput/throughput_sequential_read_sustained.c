#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define FILE_NAME "test.txt"
#define ONE_MEGABYTE (long int) 1000000
#define ONE_SECOND (long int) 1000000000
#define SECONDS 10
#define BYTE_SIZE 1024

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    struct timespec start;
    struct timespec stop;
    time_t start_outer;
    time_t stop_outer;
    long int max = 0;
    
    char buf[BYTE_SIZE];

    for (;;) {
        int bytes_read = 0;
        time_t elapsed_time = 0;
        // Open test file
        FILE* test_file = fopen(FILE_NAME, "r");

        start_outer = time(NULL);
        for (;;) {
            // Measure reading a (number of) byte(s) from the file
            while (fread(buf, sizeof(char), BYTE_SIZE, test_file) == -1) {}
            bytes_read += BYTE_SIZE;
            stop_outer = time(NULL);
            elapsed_time = difftime(stop_outer, start_outer);
            if (elapsed_time >= (double) SECONDS) {
                break;
            }
        }
        // Close test file
        fclose(test_file);
        if (bytes_read > max) {
            max = bytes_read;
            long double measured_data = (long double) max / (long double) ONE_MEGABYTE;
            printf("Measured throughput in MB/s: %Lf\n", measured_data / (long double) SECONDS);
        }
    }
}