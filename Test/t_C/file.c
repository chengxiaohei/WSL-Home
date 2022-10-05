#include <stdio.h>
#include <assert.h>

int main(){
    //读文件
    FILE *fp = fopen("tmp.txt", "r");
    char a = fgetc(fp);  //从文件流中读取一个字符
    assert(a != EOF); //确保获取到的字符不是结尾标志
    ungetc(a, fp);  //向文件流中放入一个字符
    char buf[6]={0};
    char *buff = fgets(buf, sizeof(buf), fp); //从文件流中读取N个字符(包含字符串结尾的'\0');
    assert(buff == buf);
    printf("%s\n", buf);
    fclose(fp);
    //写文件
    FILE *fp2 = fopen("tmp.txt", "w");
    fputc('a', fp2);  // 使用文件流向文件中写入一个字符
    fputc('\n', fp2);
    fputs("?????\n", fp2);  //使用文件流向文件中写入字符串
    fprintf(fp2, "hello %s\n", "changjie");  //向文件中格式化输入字符串
    fclose(fp2);
    return 0;
}