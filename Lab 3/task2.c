#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg {
    long int type;
    char txt[6];
};

int main() {
    key_t key = ftok("msgqueue", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    struct msg message;

    printf("Please enter the workspace name:\n");
    char workspace[10];
    scanf("%s", workspace);

    if (strcmp(workspace, "cse321") != 0) {
        printf("Invalid workspace name\n");
        msgctl(msgid, IPC_RMID, NULL);
        return 0;
    }

    // Log in process writes workspace name to message queue
    message.type = 1;
    strcpy(message.txt, workspace);
    msgsnd(msgid, &message, sizeof(message.txt), 0);
    printf("Workspace name sent to otp generator from log in: %s\n", message.txt);

    pid_t pid_otp = fork();

    if (pid_otp == 0) { // OTP generator process
        // Receive workspace name
        msgrcv(msgid, &message, sizeof(message.txt), 1, 0);
        printf("OTP generator received workspace name from log in: %s\n", message.txt);

        // Generate OTP
        int otp = getpid();
        snprintf(message.txt, sizeof(message.txt), "%d", otp);

        // Send OTP to log in
        message.type = 2;
        msgsnd(msgid, &message, sizeof(message.txt), 0);
        printf("OTP sent to log in from OTP generator: %s\n", message.txt);

        // Send OTP to mail
        message.type = 3;
        msgsnd(msgid, &message, sizeof(message.txt), 0);
        printf("OTP sent to mail from OTP generator: %s\n", message.txt);

        pid_t pid_mail = fork();

        if (pid_mail == 0) { // Mail process
            // Receive OTP from OTP generator
            msgrcv(msgid, &message, sizeof(message.txt), 3, 0);
            printf("Mail received OTP from OTP generator: %s\n", message.txt);

            // Send OTP back to log in
            message.type = 4;
            msgsnd(msgid, &message, sizeof(message.txt), 0);
            printf("OTP sent to log in from mail: %s\n", message.txt);
            exit(0);
        }

        wait(NULL); // Wait for mail process to terminate
        exit(0);
    }

    wait(NULL); // Wait for OTP generator process to terminate

    // Log in process receives OTP from OTP generator
    msgrcv(msgid, &message, sizeof(message.txt), 2, 0);
    char otp_from_otp[6];
    strcpy(otp_from_otp, message.txt);
    printf("Log in received OTP from OTP generator: %s\n", otp_from_otp);

    // Log in process receives OTP from mail
    msgrcv(msgid, &message, sizeof(message.txt), 4, 0);
    char otp_from_mail[6];
    strcpy(otp_from_mail, message.txt);
    printf("Log in received OTP from mail: %s\n", otp_from_mail);

    // Compare OTPs
    if (strcmp(otp_from_otp, otp_from_mail) == 0) {
        printf("OTP Verified\n");
    } else {
        printf("OTP Incorrect\n");
    }

    msgctl(msgid, IPC_RMID, NULL); // Remove message queue
    return 0;
}
