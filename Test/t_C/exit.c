#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void exit_callback(){
    printf("程序结束\n");
}

int main(){
    atexit(exit_callback);  //注册回调函数，程序正常终止时将会执行该函数
    abort();  // 令程序异常终止
    exit(EXIT_SUCCESS);  //退出程序(运行失败)
    exit(EXIT_FAILURE);  //退出程序(运行成功)
    printf("hello world\n");
    return 0;
}