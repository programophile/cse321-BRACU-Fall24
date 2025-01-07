#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <numbers>\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        // Error in forking
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process sorting
        printf("Child process: Sorting the array...\n");
        execl("./sort", "sort", argv[1], argv[2], argv[3], argv[4], (char *)NULL);  
        perror("execl failed");  // If execl fails
        exit(1);
    } else {
        wait(NULL);

        //  Odd/Even program
        printf("Parent process: Checking odd/even status...\n");
        execl("./oddeven", "oddeven", argv[1], argv[2], argv[3], argv[4], (char *)NULL);  
        perror("execl failed");  
        return 1;
    }

    return 0;
}
