#include <stdio.h>

int main(){
    int a,b,c;
    //scanf("%d%d%d", &a,&b,&c);
    //printf("a=%d,b=%d,c=%d",a,b,c);
    char x,y,z;
    //scanf("%c%c%c",&x,&y,&z);
    //printf("x=%c,y=%c,z=%c",x,y,z);
    char A[5] = {0};
    char B[5] = {0};
    char C[5] = {0};
    scanf("%s%s%s",&A,&B,&C);
    printf("A=%s,B=%s,C=%s",A,B,C);
    return 0;
}