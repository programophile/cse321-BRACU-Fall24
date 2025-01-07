#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define count_Uname 3

typedef struct {
    char* username;
    int sumAscii;
} UserData;

void* calculate_ascii_sum(void* arg) {
    UserData* data = (UserData*)arg;
    data->sumAscii = 0;
    for (int i = 0; i < strlen(data->username); i++) {
        data->sumAscii += (int)data->username[i];
    }
    return NULL;
}

void* check_results(void* arg) {
    int* final = (int*)arg;
    if (final[0] == final[1] && final[1] == final[2]) {
        printf("Youreka\n");
    } else if (final[0] == final[1] || final[1] == final[2] || final[0] == final[2]) {
        printf("Miracle\n");
    } else {
        printf("Hasta la vista\n");
    }
    return NULL;
}

int main() {
    pthread_t threads[count_Uname];
    UserData user_data[count_Uname];
    int final[count_Uname];

    char* usrName[count_Uname] = {
        "Alice",
        "Bob",
        "Charlie"
    };

    for (int i = 0; i < count_Uname; i++) {
        user_data[i].username = usrName[i];
        pthread_create(&threads[i], NULL, calculate_ascii_sum, &user_data[i]);
    }

    for (int i = 0; i < count_Uname; i++) {
        pthread_join(threads[i], NULL);
        final[i] = user_data[i].sumAscii;
    }

    pthread_t finalThread;
    pthread_create(&finalThread, NULL, check_results, final);
    pthread_join(finalThread, NULL);

    return 0;
}
