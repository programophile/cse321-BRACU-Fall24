
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
	if (sum%2==0){
		pthread_exit("Even");
}	else{
		pthread_exit("ODD");
}
}
void* thread_return; 
int main(){
        pthread_t th1;
        pthread_create(&th1,NULL,add,(void*) arr);
        pthread_join(th1,&thread_return);
	printf("The returned value is %s\n",(char*)thread_return);

}
