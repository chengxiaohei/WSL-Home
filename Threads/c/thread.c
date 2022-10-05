#include <stdio.h>
#include <pthread.h>

int Count = 0;

void *thread_count(void *arg){
    int i=0;
    while(i<500000){
        Count++;
        i++;
    }
}

int main(){
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_count, NULL);
    pthread_create(&t2, NULL, thread_count, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("result:%d\n", Count);
    return 0;
}