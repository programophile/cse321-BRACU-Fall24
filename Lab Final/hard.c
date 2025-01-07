#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int total_money = 200;
int num_users = 3;
int item_cost = 150;
sem_t vending_machine;

void* user_action(void* arg) {
    int user_id = int arg;

    printf("User %d is waiting to access the vending machine.\n", user_id);

    sem_wait(&vending_machine);

    printf("User %d is using the vending machine.\n", user_id);

    if (total_money >= item_cost) {
        total_money -= item_cost;
        printf("User %d purchased an item for $%d.\n", user_id, item_cost);
        printf("Remaining balance: $%d\n", total_money);
    } else {
        printf("User %d tried to purchase an item but had insufficient funds.\n", user_id);
        printf("Remaining balance: $%d\n", total_money);
    }

    printf("User %d has finished using the vending machine.\n", user_id);

    sem_post(&vending_machine);
    return NULL;
}

int main() {
    pthread_t* users;
    int user_ids;

   
    

    sem_init(&vending_machine, 0, 1);

   

    return 0;
}
