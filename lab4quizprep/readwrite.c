#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(){
	int n,fd1,fd2;
	char buffer[50];
	fd1=open("write_file.txt",O_RDONLY);
	n=read(fd1,buffer,50);
	fd2=open("output.txt", O_CREAT | O_WRONLY,0642);
	write(fd2,buffer,n);
	close(fd1);
	close(fd2);
	return 0;
}
