#include <stdio.h>
#include <pthread.h>

/**
 *  仅仅使用互斥锁完成了生产者消费者模型
 *  但是这样的做法还会造成很多的资源浪费
 *  也就是线程的执行完全依赖于操作系统的调度，
 *  某线程并不满足执行条件，但是系统不知道，还是把他调度来执行，这样该线程就来白跑了一圈，
 *  因此，使用条件变量就可以降低这样的资源损耗
 */
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t Cond = PTHREAD_COND_INITIALIZER;
int Count = 2;

void *Producer(){
    while(1){
        pthread_mutex_lock(&lock);
        if(Count < 9){
            Count++;
        }
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(0);
}

void *Consumer(){
    while(1){
        pthread_mutex_lock(&lock);
        if(Count > 0){
            Count--;
        }
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(0);
}

void *SuperVisioner(){
    while(1){
        pthread_mutex_lock(&lock);
        printf("%d ", Count);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(0);
}

int main(){
    pthread_t t1, t2, t3, t4;
    pthread_create(&t1, NULL, Producer, NULL);
    pthread_create(&t2, NULL, Producer, NULL);
    pthread_create(&t3, NULL, Consumer, NULL);
    pthread_create(&t4, NULL, SuperVisioner, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    return 0;
}