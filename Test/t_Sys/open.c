#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(){
    int fd = open("test.txt", O_RDONLY); //打开文件
    if(fd == -1){
        perror("open failed!\n");
    }
    struct stat sb;
    if (fstat(fd, &sb) == -1){ //获取文件描述符的状态
        perror("??");
    }
    printf("file size: %ld\n", sb.st_size);

    char buf[10] = "123456789";
    write(fd, buf, 10);
    printf("file size: %ld\n", sb.st_size);
    char *a = (char *)malloc(10);
    char *b = (char *)malloc(10);
    printf("a:%p\n", a);
    printf("b:%p\n", b);
    return 0;

}