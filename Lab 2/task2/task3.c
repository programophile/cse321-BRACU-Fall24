#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t x, y, z;
    int pCount = 1;

    x = fork();
    if (x < 0) {
        perror("no fork");
        exit(1);
    }

    if (x > 0) {
        pCount++;
        y = fork();
        
        if (y < 0) {
            perror("no fork");
            exit(1);
        }

        if (y > 0) {
            pCount++;
            z = fork();
            
            if (z < 0) {
                perror("no fork");
                exit(1);
            }

            if (z > 0) {
                pCount++;
            }
        }
    }

    pid_t currPid = getpid();
    if (x > 0) {
        wait(NULL);
    } else {
        if (currPid % 2 != 0) {
            fork();
            pCount++;
        }
    }

    if (y > 0 && x > 0) {
        wait(NULL);
    } else if (z > 0 && y > 0) {
        if (currPid % 2 != 0) {
            fork();
            pCount++;
        }
    }

    printf("Total number of processes created (including parent): %d\n", pCount);

    return 0;
}
