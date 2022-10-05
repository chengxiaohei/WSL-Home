#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>


//这是一个有Bug的代码，当生产者+消费者 > 2时，就会出现Bug

pthread_cond_t ProducerCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t ConsumerCond = PTHREAD_COND_INITIALIZER;
int Count = 0;

void *Producer(void *arg){
    pthread_mutex_t* lockp = (pthread_mutex_t *)arg;
    while(1){
        pthread_mutex_lock(lockp);
        while(!(Count != 9)){
            printf("Producer\n");
            pthread_cond_wait(&ProducerCond, lockp);  //释放锁并在Cond条件变量上等待
        }
        // 此时又自动地重新获取了锁
        assert(Count != 9);
        printf("%d ", Count++);
        pthread_cond_broadcast(&ConsumerCond);
        pthread_mutex_unlock(lockp);
    }
    pthread_exit(0);
}

void *Consumer(void *arg){
    pthread_mutex_t* lockp = (pthread_mutex_t *)arg;
    while(1){
        pthread_mutex_lock(lockp);
        while(!(Count != 0)){
            printf("Consumer\n");
            pthread_cond_wait(&ConsumerCond, lockp);  //释放锁并在Cond条件变量上等待
        }
        assert(Count != 0);
        printf("%d ", Count--);
        pthread_cond_broadcast(&ProducerCond);
        pthread_mutex_unlock(lockp);
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
    pthread_create(&t4, NULL, Consumer, &lock);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    return 0;
}