#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(){
	int n,fd1,fd2;
	char buffer[50];
	n=read(0,buffer,50);
	fd1=open("output.txt", O_WRONLY | O_CREAT | O_APPEND);
	write(fd1,buffer,n);

}
