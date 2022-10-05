#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_cond_t Cond = PTHREAD_COND_INITIALIZER;

int number = 0;
char before = '_';

void *printleft(void *arg){
    pthread_mutex_t *lockp = (pthread_mutex_t *)arg;
    while(1){
        pthread_mutex_lock(lockp);
        while(!(number >=0 && number <=2 && (before == '>' || before == '_'))){
            pthread_cond_wait(&Cond, lockp);
        }
        printf("<");
        number++; before = '<';
        pthread_cond_broadcast(&Cond);
        pthread_mutex_unlock(lockp);
    }
}

void *printright(void *arg){
    pthread_mutex_t *lockp = (pthread_mutex_t *)arg;
    while(1){
        pthread_mutex_lock(lockp);
        while(!((number >=0 && number <=2 && before == '<' || before == '_'))){
            pthread_cond_wait(&Cond, lockp);
        }
        printf(">");
        number++; before = '>';
        pthread_cond_broadcast(&Cond);
        pthread_mutex_unlock(lockp);
    }
}

void *printdown(void *arg){
    pthread_mutex_t *lockp = (pthread_mutex_t *)arg;
    while(1){
        pthread_mutex_lock(lockp);
        while(!(number == 3)){
            pthread_cond_wait(&Cond, lockp);
        }
        printf("_");
        number = 0; before = '_';
        pthread_cond_broadcast(&Cond);
        pthread_mutex_unlock(lockp);
    }
}

int main(){
    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);
    pthread_t ths[32];
    for(int i=0; i<32; i+=3){
        pthread_create(&ths[i], NULL, printleft, &lock);
        pthread_create(&ths[i+1], NULL, printright, &lock);
        pthread_create(&ths[i+2], NULL, printdown, &lock);

    }
    for(int i=0; i<32; i++){
        pthread_join(ths[i], NULL);
    }
    return 0;
}