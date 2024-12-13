#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
	int n,fd;
	char read_data[50];
	fd=open("write_file.txt", O_RDONLY);
	n= read(fd,read_data,10);
	printf("The read data is %s", read_data);
	close(fd);
	return 0;
}
