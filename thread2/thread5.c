#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int arr[2]= {10,20};
void* add(void* arg){
	int *index=arg;
	int sum= index[0]+index[1];
	printf("thread 1 , performing addition \n");
	sleep(1);
	printf("%d the sum is\n", sum);
}

void* sub(void* arg){
	int *index=arg;
	int subs= index[0]-index[1];
	printf("Thread 2 , subs\n");
	sleep(1);
	printf("The subs is %d\n",subs);

}
int main(){
	pthread_t th1,th2;
	pthread_create(&th1,NULL,add,(void*) arr);
	pthread_create(&th2,NULL,sub,(void*) arr);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
}
