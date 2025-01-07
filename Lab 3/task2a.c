#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg {
    long int type;
    char txt[10]; 
};

int main() {
    key_t key = ftok("message_queue", 123);
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

    message.type = 1;
    strncpy(message.txt, workspace, sizeof(message.txt) - 1);
    message.txt[sizeof(message.txt) - 1] = '\0';
    msgsnd(msgid, &message, sizeof(message.txt), 0);
    printf("Workspace name sent to otp generator from log in: %s\n", message.txt);

    pid_t pid_otp = fork();

    if (pid_otp == 0) { 
     
        msgrcv(msgid, &message, sizeof(message.txt), 1, 0);
        printf("OTP generator received workspace name from log in: %s\n", message.txt);

       
        int otp = getpid() % 100000; 
        snprintf(message.txt, sizeof(message.txt), "%05d", otp);

       
        message.type = 2;
        msgsnd(msgid, &message, sizeof(message.txt), 0);
        printf("OTP sent to log in from OTP generator: %s\n", message.txt);

       
        message.type = 3;
        msgsnd(msgid, &message, sizeof(message.txt), 0);
        printf("OTP sent to mail from OTP generator: %s\n", message.txt);

        pid_t pid_mail = fork();

        if (pid_mail == 0) { 
           
            msgrcv(msgid, &message, sizeof(message.txt), 3, 0);
            printf("Mail received OTP from OTP generator: %s\n", message.txt);

           
            message.type = 4;
            msgsnd(msgid, &message, sizeof(message.txt), 0);
            printf("OTP sent to log in from mail: %s\n", message.txt);
            exit(0);
        }

        wait(NULL); 
        exit(0);
    }

    wait(NULL); 


    msgrcv(msgid, &message, sizeof(message.txt), 2, 0);
    char otp_from_otp[10];
    strncpy(otp_from_otp, message.txt, sizeof(otp_from_otp) - 1);
    otp_from_otp[sizeof(otp_from_otp) - 1] = '\0';
    printf("Log in received OTP from OTP generator: %s\n", otp_from_otp);


    msgrcv(msgid, &message, sizeof(message.txt), 4, 0);
    char otp_from_mail[10];
    strncpy(otp_from_mail, message.txt, sizeof(otp_from_mail) - 1);
    otp_from_mail[sizeof(otp_from_mail) - 1] = '\0';
    printf("Log in received OTP from mail: %s\n", otp_from_mail);

    
    if (strcmp(otp_from_otp, otp_from_mail) == 0) {
        printf("OTP Verified\n");
    } else {
        printf("OTP Incorrect\n");
    }

    msgctl(msgid, IPC_RMID, NULL); 
    return 0;
}

