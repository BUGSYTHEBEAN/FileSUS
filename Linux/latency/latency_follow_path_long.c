#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define BASE_DIR "../../../../../../../../../../../../../../../"
#define DIR_ONE "test/"
#define FULL_DIR DIR_ONE "1/2/3/4/5/6/7/8/9/10/11/12/13/14"

int main(int argc, char *argv[]) {
    if (access(FULL_DIR, F_OK)) {
        rmdir(DIR_ONE);
        system("mkdir -p " FULL_DIR);
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