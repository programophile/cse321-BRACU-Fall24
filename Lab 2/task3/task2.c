#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* func_thred(void* arg) {
    int ID_thread = *((int*)arg);
    for (int i = 0; i < 5; i++) {
        printf("Thread %d prints %d\n", ID_thread, ID_thread * 5 + i + 1);
    }
    return NULL;
}

int main() {
    pthread_t threads[5];
    int numberThread[5];

    for (int i = 0; i < 5; i++) {
        numberThread[i] = i;
        pthread_create(&threads[i], NULL, func_thred, &numberThread[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
