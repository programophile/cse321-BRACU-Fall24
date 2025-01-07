#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void* block1(void* arg)
{
        for(int i = 1; i <= 5; i++)
        {
                sleep(1);
                printf("%d. I am Thread-1.\n", i);
        }
        return NULL;
}

void* block2(void* arg)
{
        for(int i = 1; i <= 10; i++)
        {
                sleep(1);
                printf("%d. I am Thread-2.\n", i);
        }
}


//Introduction to multithread
int main()
{
        pthread_t thread1, thread2;
        
        pthread_create(&thread1, NULL, block1, NULL); 
        pthread_create(&thread2, NULL, block2, NULL);
        
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        
	return 0;
}
