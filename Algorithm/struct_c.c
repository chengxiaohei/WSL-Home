#include <stdio.h>

struct A
{
    char a;
    int b;
    double c;
}__attribute__((aligned(8)));

typedef int int32_t __attribute__((aligned(4)));


int main()
{
    struct A a;
    printf("%ld\n", sizeof(a));

    printf("%ld\n", sizeof(int));
    printf("%ld\n", sizeof(int32_t));

    return 0;
}