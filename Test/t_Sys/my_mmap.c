#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/mman.h>
#include <string.h>


int main(){
    int fd = open("a.txt", O_RDWR|O_CREAT, 0644); // rw-r--r--
    if(fd == -1){
        printf("%s\n", strerror(errno));
        return -1;
    }
    truncate("a.txt", 1024); //把文件截断为1024个字节
    // mmap => 虚拟内存映射到文件(物理内存) 映射也成功
    char *p = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED){
        printf("%s\n", strerror(errno));
        close(fd);
        return -1;
    }
    // 如果文件大小为0,会出现总线错误（Bus error）
    strcpy(p, "hello world");
    munmap(p, 4096);
    close(fd);
    return 0;
}