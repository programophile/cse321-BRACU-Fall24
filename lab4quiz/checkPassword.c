#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
int main (int argc, char *argv[]) {
	int n, fd;
	char buffer[50];
	fd= open("password.txt", O_RDONLY);
	n = read(fd, buffer, 50);
	execl("./write","./write",NULL);
	printf("The read data is %s",buffer);
}
