#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "mysem.h"

#define KEY 14
#define PERMISSION 0666
#define SHARE_MEM_SIZE (4096 * 10)

int main(int argc, char *argv[]){
    int ret;
    int shmid;
    void *shmaddr;
    /* get share memory */
    shmid = shmget((key_t)KEY, SHARE_MEM_SIZE, PERMISSION);
    if(shmid == -1){
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    shmaddr = shmat(shmid, NULL, 0);
    if(shmaddr == (void *) -1){
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    
    /* get semaphore */
    int empty_semid;
    empty_semid = semget((key_t)KEY, 1, PERMISSION);
    if(empty_semid == -1){
        perror("semget");
        exit(EXIT_FAILURE);
    }
    int full_semid;
    full_semid = semget((key_t)(KEY+1), 1, PERMISSION);
    if(full_semid == -1){
        perror("semget");
        exit(EXIT_FAILURE);
    }
    while(1){
        if((ret = down(full_semid)) == -1){
            perror("down");
            exit(EXIT_FAILURE);
        }
        int *p = (int *)shmaddr;
        for(int i=0; i<10; i++){
            printf("%d\t", *p);
            p++;
        }
        printf("\n");
        if((ret = up(empty_semid)) == -1){
            perror("up");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}