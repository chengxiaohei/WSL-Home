#include <stdio.h>
#include <pthread.h>

int Count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *thread_count(void *arg){
    int i = 500000000;
    while(i-- > 0){
        pthread_mutex_lock(&lock);                                                                                                                                                                                                           
        Count++;
        pthread_mutex_unlock(&lock);
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