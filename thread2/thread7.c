#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* block9(int *n){
	printf("Entered the thread\n");
	if(*n%2==0){
		pthread_exit("Even");
	}else{
		pthread_exit("ODD");
}


}

int num=10;
void* thread_return;
int main(){
	pthread_t th1;
	pthread_create(&th1,NULL,(void*)block9, &num);
	pthread_join(th1,&thread_return);
	printf("Thread returned: %s\n",(char*)thread_return);
	return 0;

}
