#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <io.h>
#include <process.h>
#include <stdlib.h>
#include <time.h>

#define UP_ONE_DIR ".."
#define DIR_NAME "test"
#define F_OK 0

int main(int argc, char *argv[]) {
    if (access(DIR_NAME, F_OK)) {
        if (mkdir(DIR_NAME, 0777) == -1) {
            printf("Error making directory\n");
            exit(1);
        }
    }
    struct timespec start;
    struct timespec stop;
    long int min = 100000;
    
    for (;;) {
        // Start clock
        if(timespec_get(&start, TIME_UTC) != TIME_UTC){
            exit(1);
            //error
        }
        // Change directory to newly created one
        if (chdir(DIR_NAME) != 0) {
            perror("cd failed");
            exit(1);
        }
        
        if(timespec_get(&stop, TIME_UTC) != TIME_UTC){
            exit(1);
            //error
        }
        // Go back up
        if (chdir(UP_ONE_DIR) != 0) {
            perror("cd failed");
            exit(1);
        }
        long int current = stop.tv_nsec - start.tv_nsec;
        if (current < min && current > 0) {
            min = current;
            printf("Elapsed time in nanoseconds: %li\n", min);
        }
    }
}