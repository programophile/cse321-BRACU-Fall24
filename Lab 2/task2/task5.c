#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t childPID, grndChildPID;
    printf("Parent process ID: %d\n", getpid());
    childPID = fork();
    if (childPID < 0) {
        perror("no fork");
        exit(1);
    }
    if (childPID == 0) {
        printf("Child process ID: %d\n", getpid());
        for (int i = 0; i < 3; i++) {
            grndChildPID = fork();
            if (grndChildPID < 0) {
                perror("no fork");
                exit(1);
            }
            if (grndChildPID == 0) {
                printf("Grandchild process ID: %d\n", getpid());
                exit(0);
            }
        }
        for (int i = 0; i < 3; i++) {
            wait(NULL);
        }
        exit(0);
    }
    wait(NULL);
    return 0;
}
