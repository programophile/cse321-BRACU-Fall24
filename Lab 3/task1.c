#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

struct shared {
    char sel[100];
    int b;
};

int main() {
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key, sizeof(struct shared), 0666|IPC_CREAT);
    struct shared *shm = (struct shared*) shmat(shmid, NULL, 0);

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    printf("Provide Your Input From Given Options:\n");
    printf("1. Type a to Add Money\n");
    printf("2. Type w to Withdraw Money\n");
    printf("3. Type c to Check Balance\n");

    fgets(shm->sel, 100, stdin);
    shm->sel[strcspn(shm->sel, "\n")] = '\0';
    shm->b = 1000; // Initialize balance

    printf("Your selection: %s\n", shm->sel);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) { // Child process
        close(pipefd[0]);

        if (strcmp(shm->sel, "a") == 0) {
            int addAmount;
            printf("Enter amount to be added:\n");
            scanf("%d", &addAmount);
            if (addAmount > 0) {
                shm->b += addAmount;
                printf("Balance added successfully\n");
                printf("Updated balance after addition:\n%d\n", shm->b);
            } else {
                printf("Adding failed, Invalid amount\n");
            }
        } else if (strcmp(shm->sel, "w") == 0) {
            int withdrawAmount;
            printf("Enter amount to be withdrawn:\n");
            scanf("%d", &withdrawAmount);
            if (withdrawAmount > 0 && withdrawAmount <= shm->b) {
                shm->b -= withdrawAmount;
                printf("Balance withdrawn successfully\n");
                printf("Updated balance after withdrawal:\n%d\n", shm->b);
            } else {
                printf("Withdrawal failed, Invalid amount\n");
            }
        } else if (strcmp(shm->sel, "c") == 0) {
            printf("Your current balance is:\n%d\n", shm->b);
        } else {
            printf("Invalid selection\n");
        }

        write(pipefd[1], "Thank you for using", 20);
        close(pipefd[1]);
        exit(0);
    } else { // Parent process
        close(pipefd[1]);

        wait(NULL);
        char buffer[100];
        read(pipefd[0], buffer, sizeof(buffer));
        printf("%s\n", buffer);
        close(pipefd[0]);

        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
