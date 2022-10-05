#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/**
 *  这里是将pthread_mutex_t互斥锁从全局变量区搬到了程序主线程的栈帧中
 *  然后通过指针的方式传递给各个线程
 */
int Count = 2;

void *Producer(void *arg){
    pthread_mutex_t* lock = (pthread_mutex_t *)arg;
    while(1){
        pthread_mutex_lock(lock);
        if(Count < 9){
            Count++;
        }
        pthread_mutex_unlock(lock);
    }
    pthread_exit(0);
}

void *Consumer(void *arg){
    pthread_mutex_t* lock = (pthread_mutex_t *)arg;
    while(1){
        pthread_mutex_lock(lock);
        if(Count > 0){
            Count--;
        }
        pthread_mutex_unlock(lock);
    }
    pthread_exit(0);
}

void *SuperVisioner(void *arg){
    pthread_mutex_t* lock = (pthread_mutex_t *)arg;
    while(1){
        pthread_mutex_lock(lock);
        printf("%d ", Count);
        pthread_mutex_unlock(lock);
    }
    pthread_exit(0);
}

int main(){
    pthread_t t1, t2, t3, t4;
    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&t1, NULL, Producer, &lock);
    pthread_create(&t2, NULL, Producer, &lock);
    pthread_create(&t3, NULL, Consumer, &lock);
    pthread_create(&t4, NULL, SuperVisioner, &lock);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    return 0;
}