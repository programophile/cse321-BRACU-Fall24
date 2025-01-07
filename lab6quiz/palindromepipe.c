#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
int is_palindrome(const char *str) {
    int len = strlen(str);
    int i;
    for (i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0; // Not a palindrome
        }
    }
    return 1; 
}


int main(){
	int fd[2];
	pid_t a;
	char buff[200];
	
	int p=pipe(fd);
	if(p==-1){
		perror("pipe");
	}
	
	a=fork();
	if(a<0){
		perror("fork");
	}
	
	else if(a>0){
	
		close(fd[0]);
		printf("Give input:\n");
		read(0,buff,sizeof(buff));
		printf("Writing data for sending_____\n");
		write(fd[1],buff,sizeof(buff));
		printf("Writing done_____\n");
		close(fd[1]);
		
	}
	
	else{
		close(fd[1]);
		printf("Reading data after receiving_____\n");
		read(fd[0],buff,sizeof(buff));
		if (is_palindrome(buff)){
				printf("The word '%s' is a palindrome.\n", buff);

			}
		else{
				printf("The word '%s' is not  a palindrome.\n", buff);
		}
		close(fd[0]);
	}


	return 0;
}

