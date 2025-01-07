#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread1(void* arg){
	for(int i=1;i<=12;i++){
		sleep(1);
		printf("%d . i am thread 1\n", i);
	}
}
void* thread2(void* arg){
	for(int i=0; i<=3;i++){
		sleep(1);
		printf("%d . I am thread 2\n",i);
}
}

int main(){
	pthread_t th1, th2;
	pthread_create(&th1,NULL,thread1,NULL);
	pthread_create(&th2,NULL,thread2,NULL);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);

	return 0;

}
