#include <stdio.h>

int func(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    int a = 1;
    int b = 2;
    int c[20] = {0};
    int *p = &arg6;
    return a;
}

int main(int argc, char *argv[], char *envs[])
{
    printf("Hello world\n");
    for(int i=0; envs[i] != NULL; i++){
        printf("%s\n", envs[i]);
    }
    return  1;
}