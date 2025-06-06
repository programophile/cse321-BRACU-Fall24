#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

// Function prototype for is_palindrome
int is_palindrome(const char *str);

int main() {
    int fd[2];
    pid_t a;
    char buff[200];

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    a = fork();
    if (a < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (a > 0) { // Parent process
        close(fd[0]); // Close the read end of the pipe

        printf("Give input:\n");
        ssize_t bytes_read = read(0, buff, sizeof(buff) - 1); // Reserve space for null terminator
        if (bytes_read > 0) {
            buff[bytes_read] = '\0'; // Null-terminate the input
            // Remove trailing newline if present
            char *newline = strchr(buff, '\n');
            if (newline) {
                *newline = '\0';
            }

            printf("Writing data for sending_____\n");
            write(fd[1], buff, strlen(buff) + 1); // Write null-terminated string
            printf("Writing done_____\n");
        }

        close(fd[1]); // Close the write end of the pipe
    } else { // Child process
        close(fd[1]); // Close the write end of the pipe

        printf("Reading data after receiving_____\n");
        ssize_t bytes_read = read(fd[0], buff, sizeof(buff) - 1);
        if (bytes_read > 0) {
            buff[bytes_read] = '\0'; // Null-terminate the received data
            if (is_palindrome(buff)) {
                printf("The word '%s' is a palindrome.\n", buff);
            } else {
                printf("The word '%s' is not a palindrome.\n", buff);
            }
        }

        close(fd[0]); // Close the read end of the pipe
    }

    return 0;
}

// Function to check if a string is a palindrome
int is_palindrome(const char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0; // Not a palindrome
        }
    }
    return 1; // Palindrome
}
