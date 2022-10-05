#include <cstdio>

int test1(int a, int b) {
    return a+b;
}
void test2() {
    char* str = "hello~";
    str[0] = '0'; //段错误程序终止,生成core文件
}
void test3() {
    printf("world~~\n");
}

int main() {
    test1(1, 2);
    test2();
    test3();

    return 0;
}

