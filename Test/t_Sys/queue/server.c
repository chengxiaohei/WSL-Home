#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

// 用于创建一个唯一的key
#define KEY 1234

// 消息结构
struct msgbuf {
    long mtype;
    char mtext[256];
};

int main()
{
    int msqid;
    key_t key;
    struct msgbuf msg;

    // 打印key值
    printf("Message Queue - Server key is: %d.\n", KEY);

    // 创建消息队列
    if ((msqid = msgget((key_t)KEY, IPC_CREAT | 0666)) == -1)
    {
        perror("msgget error");
        exit(EXIT_FAILURE);
    }

    // 打印消息队列ID及进程ID
    printf("My msqid is: %d.\n", msqid);
    printf("My pid is: %d.\n", getpid());

    // 循环读取消息
    while(true) 
    {
        msgrcv(msqid, &msg, 256, 888, 0);// 接收类型为888的第一个消息
        printf("Server: receive msg.mtype is: %ld.\n", msg.mtype);
        printf("Server: receive msg.mtext is: %s.\n", msg.mtext);

        msg.mtype = 999; // 客户端接收的消息类型
        sprintf(msg.mtext, "hello, I'm server %d", getpid());
        msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
    }
    return 0;
}