#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    pid_t pid;
    int status;
    char pass[100];
    printf("Enter Pass");
    scanf("%s",&pass);
    int fd,fd2;
    char buffer[100];

    pid = fork(); 

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("Child proces Started");
	fd=open("password.txt",O_WRONLY|O_CREAT,0644);
	write(fd,pass,sizeof(pass));
	
        printf("pass saved.\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("Waiting for child process to finish...\n");
        wait(&status);
	fd2=open('password.txt', O_RDWR);
	read(fd2,buffer,sizeof[buffer]); 
        printf("password from the file %s",&buffer);
	int contains_digit = 0;
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (isdigit(buffer[i])) {
                contains_digit = 1;
                	
                break;
            }
        }
    }

    return EXIT_SUCCESS;
}
