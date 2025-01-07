#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

void *thread_func(void* arg){
	for(int i=1;i<=15;i++){
	sleep(1);
	printf("%d . I am Thread-1\n",i);
}
}

void default_thread(){
	 for(int i=1;i<=3;i++){
		sleep(1);
		printf("%d . I am deafult thread\n",i);
}
}

int main()
{
        pthread_t thread1;
           
        pthread_create(&thread1, NULL, thread_func, NULL);
        default_thread();
       
        pthread_join(thread1, NULL);
        
	return 0;
} 
