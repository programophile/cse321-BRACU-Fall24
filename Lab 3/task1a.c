#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

struct shared {
    char choice[100];
    int balance;
};

int main() {
 
    key_t key = ftok("shared_file", 123);
    
  
    int shm_id = shmget(key, sizeof(struct shared), 0666 | IPC_CREAT);
    struct shared *shared = (struct shared *)shmat(shm_id, NULL, 0);

 
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    printf("Provide Your Input From Given Options:\n");
    printf("1. Type a to Add Money\n");
    printf("2. Type w to Withdraw Money\n");
    printf("3. Type c to Check Balance\n");

    fgets(shared->choice, sizeof(shared->choice), stdin);
    shared->choice[strcspn(shared->choice, "\n")] = '\0';
    shared->balance = 1000; 

    printf("Your selection: %s\n", shared->choice);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) { 
        close(pipe_fd[0]);

        if (strcmp(shared->choice, "a") == 0) {
            int addAmount;
            printf("Enter amount to be added:\n");
            scanf("%d", &addAmount);
            if (addAmount > 0) {
                shared->balance += addAmount;
                printf("Balance added successfully\n");
                printf("Updated balance after addition:\n%d\n", shared->balance);
            } else {
                printf("Adding failed, Invalid amount\n");
            }
        } else if (strcmp(shared->choice, "w") == 0) {
            int withdrawAmount;
            printf("Enter amount to be withdrawn:\n");
            scanf("%d", &withdrawAmount);
            if (withdrawAmount > 0 && withdrawAmount <= shared->balance) {
                shared->balance -= withdrawAmount;
                printf("Balance withdrawn successfully\n");
                printf("Updated balance after withdrawal:\n%d\n", shared->balance);
            } else {
                printf("Withdrawal failed, Invalid amount\n");
            }
        } else if (strcmp(shared->choice, "c") == 0) {
            printf("Your current balance is:\n%d\n", shared->balance);
        } else {
            printf("Invalid selection\n");
        }

        write(pipe_fd[1], "Thank you for using", 20);
        close(pipe_fd[1]);
        exit(0);
    } else { 
        close(pipe_fd[1]);

        wait(NULL);
        char buffer[100];
        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("%s\n", buffer);
        close(pipe_fd[0]);

        shmdt(shared);
        shmctl(shm_id, IPC_RMID, NULL);
    }

    return 0;
}

