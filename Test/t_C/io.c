#include <stdio.h>
#include <assert.h>

int main(){
    // I/O输入
    char a = getc(stdin); // 从标准输入读取一个字符
    char b = getchar(); // 从标准输入读取一个字符
    char buf[128] = {0};
    scanf("%s", buf);  // 从标准输入读取一个字符串(以空格、制表符、回车为分隔符)
    //I/O输出
    putc(a, stdout); //向标准输出打印一个字符
    putchar(b);  //向标准输出打印一个字符
    putchar('\n');
    printf("%s\n", buf);  //向标准输出打印字符串
    return 0;
}