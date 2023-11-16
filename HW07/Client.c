#include "MyMsg.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {

    key_t mykey = ftok("mymsgkey", 1);
    int msqid = msgget(mykey, IPC_CREAT);

    char string[100];

    MsgIO msgIn;
    MsgIO msgOut;

    puts("Lowercase to Uppercase");
    puts("Input string");
    while (1) {
        printf("<<< ");

        scanf("%s", string);
        fflush(stdout);
        fflush(stdin);

        memset(&msgIn, 0x00, sizeof(MsgIO));
        msgIn.mtype = MSG_TYPE_IN;
        strcpy(msgIn.str, string);
        msgsnd(msqid, &msgIn, MSG_SIZE_IN, 0);

        memset(&msgOut, 0x00, sizeof(MsgIO));
        memset(&msgOut.str, 0x00, sizeof(msgOut.str));
        msgrcv(msqid, &msgOut, MSG_SIZE_OUT, MSG_TYPE_OUT, 0);
        printf(">>> %s\n", msgOut.str);
    }
    return 0;
}
