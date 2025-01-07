#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


int var = 0;
void* block3(void* arg)
{
	var++;
}

int main()
{
	pthread_t thread [3];
	for (int i = 0; i < 3; i++)
	{
		pthread_create(&thread[i], NULL, block3, NULL);
		pthread_join(thread[i], NULL);
		printf("Thread: %d has started running.\n", i);
		printf("Thread: %d has ended.\n", i);
	}	
	printf("The threads have all ended and var is: %d.\n", var);
}
