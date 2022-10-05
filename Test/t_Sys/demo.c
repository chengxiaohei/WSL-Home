#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

// 创建守护进程

volatile sig_atomic_t running = 1;
void sigint_handler(int sig){
    running = 0;
}

int main(){
    int id = fork();
    if(id == -1){
        perror("fork");
        return -1;
    }
    if(id > 0){  //令父进程退出
        return 0; 
    }

    printf("pid:%d\n", getpid());
    setsid();
    chdir("/");
    umask(0);
    for(int i=0; i<3; i++){
        close(i);
    }
    signal(SIGINT, sigint_handler);
    while(running){
        int fd = open("/tmp/dameon.log", O_CREAT|O_WRONLY|O_APPEND, 0644);
        if(fd == -1){
            perror("open");
            return -1;
        }
        char *p = "这是一个守护进程";
        write(fd, p, strlen(p));
        close(fd);
        sleep(3);
    }
    return 0;
}