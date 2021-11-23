#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <time.h>

#define UP_ONE_DIR ".."
#define FILE_NAME "test.txt"

int main(int argc, char *argv[]) {
    FILE* fd = fopen(FILE_NAME, "w");
    fputc(69, fd);
    fclose(fd);

    //struct timeb start, stop;
    struct timespec start, stop;
    long int min = 100000;
    
    char buf[1];

    for (;;) {
        // Open test file
        FILE* test_file = fopen(FILE_NAME, "r");
        while (test_file == NULL) {
            test_file = fopen(FILE_NAME, "r");
        }
        // Start clock
        //ftime(&start);
        if(timespec_get(&start, TIME_UTC) != TIME_UTC){
            exit(1);
            //error
        }
        while (fclose(test_file)) {}
        // Stop clock
        //ftime(&stop);
        if(timespec_get(&stop, TIME_UTC) != TIME_UTC){
            exit(1);
            //error
        }
        long int current = (int) stop.tv_nsec - start.tv_nsec;
        if (current < min && current > 0) {
            min = current;
            printf("Elapsed time in nanoseconds: %li\n", min);
        }
    }
}