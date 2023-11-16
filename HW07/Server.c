#include "MyMsg.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

void signalHandler(int signum);
char *toUpper(char str[]);

key_t mykey = 0;
int msqid = 0;

int main(int argc, char const *argv[]) {

    MsgIO msgIn;
    MsgIO msgOut;

    mykey = ftok("mymsgkey", 1);             // 키생성
    msqid = msgget(mykey, IPC_CREAT | 0600); // 메시지큐생성

    signal(SIGINT, signalHandler);

    while (1) {
        puts("Wait ...");

        memset(&msgIn, 0x00, sizeof(MsgIO));
        msgrcv(msqid, &msgIn, MSG_SIZE_IN, MSG_TYPE_IN, 0);
        printf("Receive: %s\n", msgIn.str);

        memset(&msgOut, 0x00, sizeof(MsgIO));
        msgOut.mtype = MSG_TYPE_OUT;
        strcpy(msgOut.str, toUpper(msgIn.str));
        msgsnd(msqid, &msgOut, MSG_SIZE_OUT, 0);
        printf("send: %s\n", msgOut.str);

        fflush(stdout);
    }
    return 0;
}

void signalHandler(int signum) {
    if (signum == SIGINT) {
        msgctl(msqid, IPC_RMID, NULL);
        exit(0);
    }
}

char *toUpper(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = str[i] - 32;
    }
    return str;
}
