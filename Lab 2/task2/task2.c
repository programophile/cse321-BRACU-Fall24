#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t childID, grandChildID;
    childID = fork();

    if (childID < 0) {
        perror("no fork");
        exit(1);
    } else if (childID == 0) {
        grandChildID = fork();

        if (grandChildID < 0) {
            perror("no fork");
            exit(1);
        } else if (grandChildID == 0) {
            printf("I am grandchild\n");
            exit(0);
        } else {
            wait(NULL);
            printf("I am child\n");
            exit(0);
        }
    } else {
        wait(NULL);
        printf("I am parent\n");
    }
    return 0;
}
