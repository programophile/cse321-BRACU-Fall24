#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(){
	int n,fd;
	char password[]="12345";
	fd= open("password.txt", O_WRONLY | O_CREAT,0644);
	write(fd,password,sizeof(password));
	printf("The write data is %s",password);
	close(fd);
	return 0;
}
