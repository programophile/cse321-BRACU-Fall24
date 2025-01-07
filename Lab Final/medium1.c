#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

int main() {
    pid_t pid;
    int status;
    char pass[100];
    printf("Enter Pass: ");
    scanf("%s", pass); 

    int fd;
    char buffer[100];

    pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // 
        printf("Child process started.\n");
        fd = open("password.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("Failed to open file");
            exit(EXIT_FAILURE);
        }
        write(fd, pass, strlen(pass)); 
        close(fd); 
        printf("Password saved.\n");
        exit(EXIT_SUCCESS);
    } else { 
        printf("Waiting for child process to finish...\n");
        wait(&status);

        fd = open("password.txt", O_RDONLY);
        if (fd == -1) {
            perror("Failed to open file");
            exit(EXIT_FAILURE);
        }
        read(fd, buffer, sizeof(buffer) - 1); 
        buffer[100]; /
        close(fd);

        printf("Password from the file: %s\n", buffer);

        int contains_digit = 0;
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (isdigit(buffer[i])) {
                contains_digit = 1;
                break;
            }
        }

        if (contains_digit) {
            printf("The password contains at least one integer.\n");
        } else {
            printf("The password does not contain any integers.\n");
        }
    }

    return EXIT_SUCCESS;
}

