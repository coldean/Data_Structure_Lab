#ifndef __MYMSG_H__
#define __MYMSG_H__

#define MSG_TYPE_IN 1
#define MSG_TYPE_OUT 2
#define MSG_SIZE_IN (sizeof(MsgIO) - sizeof(long))
#define MSG_SIZE_OUT (sizeof(MsgIO) - sizeof(long))

#define MAX_BUFF 512

struct __MsgIO {
    long mtype;
    char str[MAX_BUFF];
};
typedef struct __MsgIO MsgIO;

#endif //!__MYMSG_H__
