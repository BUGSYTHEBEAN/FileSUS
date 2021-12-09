#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#define UP_ONE_DIR ".."
#define FILE_NAME "test.txt"

int main(int argc, char *argv[]) {
    FILE* fd = fopen(FILE_NAME, "w");
    fputc(69, fd);
    fputc(69, fd);
    fclose(fd);

    struct timespec start;
    struct timespec stop;
    long int min = 1000000;
    
    char buf[1];

    for (;;) {
        // Open test file
        FILE* test_file = fopen(FILE_NAME, "r");
        
        while (fread(buf, 1, 1, test_file) != 1) {}// read first byte
        // Start clock
        if(timespec_get(&start, TIME_UTC) != TIME_UTC){
            exit(1);
            //error
        }
        // Measure reading a byte from the file
        
        while (fread(buf, 1, 1, test_file) != 1) {} // read sec byte
        // Stop clock
        if(timespec_get(&stop, TIME_UTC) != TIME_UTC){
            exit(1);
            //error
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