#include <stdio.h>
#include <string.h>
#include <wchar.h>

int main(){
    
    char s[] = "你好";   //数组s中存储的就是"你好"的UTF-8编码
    printf("s数组的大小: %ld\n", sizeof(s));
    printf("s数组的长度: %ld\n", strlen(s));
    printf("%s\n", s);
    unsigned char *p = s;
    for(int i=0; i<sizeof(s); i++){
        printf("%#x ", p[i]);
    }printf("\n");

    wchar_t s1[] = L"你好";  //数组s1中存储的就是"你好"的Unicode编码,Unicode编码一个字符占用4个字节
    printf("s1数组的大小: %ld\n", sizeof(s1));
    printf("s1数组的长度: %ld\n", wcslen(s1));
    wprintf("%ls\n", s1);
    unsigned char *p1 = s1;
    for(int i=0; i<sizeof(s1); i++){
        printf("%#x ", p1[i]);
    }printf("\n");

    return 0;
}