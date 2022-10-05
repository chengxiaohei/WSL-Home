#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

// 用于创建一个唯一的key
// #define MSG_FILE "/etc/passwd"
#define KEY 1234

// 消息结构
struct msg_form {
    long mtype;
    char mtext[256];
};

int main()
{
    int msqid;
    struct msg_form msg;

    // 打印key值
    printf("Message Queue - Client key is: %d.\n", KEY);

    // 打开消息队列
    if ((msqid = msgget((key_t)KEY, IPC_CREAT | 0666)) == -1) 
    {
        perror("msgget error");
        exit(EXIT_FAILURE);
    }

    // 打印消息队列ID及进程ID
    printf("My msqid is: %d.\n", msqid);
    printf("My pid is: %d.\n", getpid());

    // 添加消息，类型为888
    msg.mtype = 888;
    sprintf(msg.mtext, "hello, I'm client %d", getpid());
    msgsnd(msqid, &msg, sizeof(msg.mtext), 0);

    // 读取类型为999的消息
    msgrcv(msqid, &msg, 256, 999, 0);
    printf("Client: receive msg.mtype is: %ld.\n", msg.mtype);
    printf("Client: receive msg.mtext is: %s.\n", msg.mtext);
    return 0;
}
