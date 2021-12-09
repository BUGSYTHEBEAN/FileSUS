#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define BASE_DIR "../../../../../../../../../../../../../../../"
#define DIR_ONE "test/"
#define FULL_DIR DIR_ONE "1/2/3/4/5/6/7/8/9/10/11/12/13/14"
#define F_OK 0

int main(int argc, char *argv[]) {
    if (access(FULL_DIR, F_OK)) {
        rmdir(DIR_ONE);
        system("mkdir -p " FULL_DIR);
    }
    struct timespec start;
    struct timespec stop;
    long int min = 1000000;
    
    for (;;) {
        // Start clock
        if(timespec_get(&start, TIME_UTC) != TIME_UTC){
            exit(1);
            //error
        }
        // Change directory to newly created one
        if (chdir(FULL_DIR) != 0) {
            perror("cd failed");
            exit(1);
        }
        
        if(timespec_get(&stop, TIME_UTC) != TIME_UTC){
            exit(1);
            //error
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