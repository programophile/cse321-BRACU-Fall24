#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
	printf("PID of exc1 -= %d", getpid());
	execl("./ex2","./ex2",NULL);
	return 0;
}
