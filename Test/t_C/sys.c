#include <stdio.h>
#include <stdlib.h>

int main(){
    // 在程序内执行终端程序
    system("echo hello > tmp.txt");
    //system("man 7 time");
    
    // 获取环境变量
    char *s = getenv("HOSTTYPE");
    if(s){
        printf("%s\n", s);
    }else{
        printf("%s\n", "not found HOTYPE envirment variable");
    }
    return 0;
}