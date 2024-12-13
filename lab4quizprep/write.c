#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
	int n,fd;
	char write_data[]="Sad Yeamin Sayem";
	fd=open("write_file.txt", O_WRONLY | O_CREAT,0644);
	write(fd,write_data,sizeof(write_data));
	close(fd);
	return 0;
}
