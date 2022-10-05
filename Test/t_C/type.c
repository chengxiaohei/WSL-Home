#include <sys/types.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>

int main(){
    int a = 0b1001010;  // 二进制
    a = 0b10101;
    int b = 0333;  //八进制
    int c = 0x123;  //十六进制

    float d = 12.0f;
    double e = 0.235f;
    printf("%lf %lf\n", d, e);

    unsigned long f = 45645UL;
    unsigned long long g = 53ULL;
    printf("%lld\n", g);
    return 0;
}