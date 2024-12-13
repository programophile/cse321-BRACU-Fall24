#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main () {
	int n, fd1, fd2;
	char buffer[18];
	fd1 = open("output.txt", O_RDWR); //abcdHello1234World
	read(fd1 , buffer, 4); //abcd
	write(1, buffer, 4);
	read(fd1, buffer, 5); //Hello, reads the next 5 character as indicated by bytes read
	write(1, buffer, 5);

}
