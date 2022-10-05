#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

volatile static int alarm_fired = 0;

void ouch(int sig){
    alarm_fired = 1;
}

int main(int argc, char *argv[]){
    int ret;
    // if(argc != 3){
    //     fprintf(stderr, "too few argument\n");
    //     fprintf(stderr, "Usage:\n");
    //     fprintf(stderr, "\t%s <pid_t> <sig>", argv[0]);
    //     exit(EXIT_FAILURE);
    // }
    // ret = kill(atoi(argv[1]), atoi(argv[2]));
    // if(ret == -1){
    //     perror("kill");
    //     exit(EXIT_FAILURE);
    // }
    signal(SIGALRM, ouch);
    ret = alarm(5); // 5秒后向当前进程发送SIGALRM信号
    printf("ret: %d\n", ret);
    fflush(stdout);
    while(1){
        if(alarm_fired) return 0;
    }
    return 0;
}