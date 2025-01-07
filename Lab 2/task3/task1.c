#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* functoin_Thrd(void* arg) {
    int number_Thread = *((int*)arg);
    printf("thread-%d running\n", number_Thread);
    printf("thread-%d closed\n", number_Thread);
    return NULL;
}

int main() {
    pthread_t threads[5];
    int threadNum[5];

    for (int i = 0; i < 5; i++) {
        threadNum[i] = i + 1;
        pthread_create(&threads[i], NULL, functoin_Thrd, &threadNum[i]);
        pthread_join(threads[i], NULL);
    }

    return 0;
}
