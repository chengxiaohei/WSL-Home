#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

// 信号量是什么东西呢？其实就是表示一个数字是不是0,
// sem_wait等待的信号量不为零时，继续运行，不阻塞

// int Num = 64;
int rings[3];

sem_t semBlank;  //空格子信号量
sem_t semData;  //数据信号量

void *Producer(){
    int step = 0;  //start pos
    while(1){
        sem_wait(&semBlank);
        int data = rand()%1234;
        rings[step] = data;
        step++;
        step %= 3;  //ring struct
        sem_post(&semData);
        printf("producer done~: %d\n", data);
        // sleep(2);
    }
}

void *Consumer(){
    int step = 0;
    while(1){
        sem_wait(&semData);
        int data = rings[step];
        step++;
        step %= 3;
        sem_post(&semBlank);
        printf("consumer done~: %d\n", data);
    }
}

int main(){
    pthread_t t1, t2, t3, t4;
    sem_init(&semBlank, 0, 3);
    sem_init(&semData, 0, 0);
    pthread_create(&t1, NULL, Producer, NULL);
    // pthread_create(&t2, NULL, Producer, NULL);
    pthread_create(&t3, NULL, Consumer, NULL);
    // pthread_create(&t4, NULL, Consumer, NULL);
    pthread_join(t1, NULL);
    // pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    // pthread_join(t4, NULL);
    return 0;
}