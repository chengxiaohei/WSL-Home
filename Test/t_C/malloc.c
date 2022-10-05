#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
    //malloc: 分配一块足以存放大小为size的存储,返回该存储块的地址,不能满足时返回NULL
    int *data = (int *)malloc(sizeof(int) * 10);
    if(data){
        for(int i=0; i<10; i++){
            printf("%d ", data[i]);
        }
        printf("\n");
    }
    free(data);
    //calloc:分配一块存储，其中足以存放n个大小为size的对象，
    //并将所有字节用0字符填充。返回该存储块的地址。不能满足时返回NULL
    int *data2 = (int *)calloc(10, sizeof(int));
    if(data2){
        for(int i=0; i<10; i++){
            data2[i] = 2;
        }
    }
    // 将p所指存储块调整为大小size，返回新块的地址。如能满足要求，新块的内容与原块一致；不能满足要求时返回NULL，此时原块不变
    int *data3 = (int *)realloc(data2, 20);
    if(data3){
        for(int i=0; i<20; i++){
            printf("%d ", data3[i]);
        }
    };
    free(data3);
    return 0;
}