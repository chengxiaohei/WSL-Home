#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#define _PATH_ "/tmp/file.tmp"
#define _SIZE_ 100

int main(){
    int ret;
    // ret = mkfifo(_PATH_, 0666 | S_ISFIFO);  // 将文件指定为命名管道
    ret = mkfifo(_PATH_, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
    if(ret == -1){
        perror("mkfifo");
		exit(EXIT_FAILURE);
    }

    int cpid = fork();
    if(cpid == 0){ // child process, used for pop 
        int fd = open(_PATH_, O_RDONLY);
        int output_fd = open("out.txt", O_WRONLY | O_APPEND);
        if(fd < 0 || output_fd < 0){
            perror("child process open");
            exit(EXIT_FAILURE);
        }
        char buf[_SIZE_];
        while(true){
            memset(buf, 0, _SIZE_);
            ret = read(fd, &buf, _SIZE_);
            if(ret == 0){
                continue;
            }
            write(output_fd, &buf, strlen(buf));
            write(output_fd, "\n", 1);
            if(strncmp(buf, "exit", 4) == 0){
                break;
            }
        }
        _exit(EXIT_SUCCESS);
    }else{ // father process, used for push
        int fd = open(_PATH_, O_WRONLY);
        if(fd < 0){
            perror("father process open");
            exit(EXIT_FAILURE);
        }
        char buf[_SIZE_];
        while(true){
            printf("father: please input:\n");
            memset(buf, 0, _SIZE_);
            scanf("%s", buf);
            write(fd, buf, strlen(buf));
            // write(fd, "\n", 1);
            if(ret < 0){
                perror("father: write");
                exit(EXIT_FAILURE);
            }
            if(strncmp(buf, "exit", 4) == 0){
                break;
            }
        }
        close(fd);
        wait(NULL);
    }
    return 0;
}