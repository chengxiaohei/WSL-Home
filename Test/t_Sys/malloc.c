#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    // printf("%d\n", getpagesize());
    // char *pa = malloc(4);
    // for(int i=32; i<32*4*1024; i++){
    //     pa[i] = 'a';
    // }
    // char *ps = malloc(4);
    int *p = (int *)malloc(sizeof(int));
    int *p1 = (int *)malloc(sizeof(int));
    p[1] = 0;
    p[2] = 1;
    p[3] = 2;
    p[4] = 2;
    p[5] = 2;
    p[6] = 2;
    p[7] = 2;
    p[8] = 2;
    p[9] = 2;
    p[10] = 2;
    printf("%d\n", *p);
    printf("%d\n", *p1);

    free (p);
    return 0;

}