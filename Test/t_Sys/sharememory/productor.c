#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "mysem.h"

#define KEY 14
#define PERMISSION 0666
#define SHARE_MEM_SIZE (4096 * 10)

void detach_shm(void *shmaddr);
void free_shm(int shmid);
void free_sem(int semid);

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Recommend Usage: %s <num>\n", argv[0]);
    }
    int ret;
    /* share memory init*/
    int shmid;
    void *shmaddr;
    shmid = shmget((key_t)KEY, SHARE_MEM_SIZE, PERMISSION | IPC_CREAT | IPC_EXCL);
    if(shmid == -1 && errno == EEXIST) {
        printf("Specified share memory existed with at least %d byte and we will use it\n", SHARE_MEM_SIZE);
        shmid = shmget((key_t)KEY, SHARE_MEM_SIZE, PERMISSION);
        if(shmid == -1){
            perror("shmget");
            exit(EXIT_FAILURE);
        }
    } else {
        if(shmid == -1) {
            perror("shmget");
            exit(EXIT_FAILURE);
        }
        printf("created a share memory with size: %d byte, shmid = %d\n", SHARE_MEM_SIZE, shmid);
    }
    shmaddr = shmat(shmid, NULL, 0);  // attach
    if(shmaddr == (void *) -1){
        perror("shmat");
        // free_shm(shmid);
        goto FREE_SHM;
        exit(EXIT_FAILURE);
    }
    /* semaphore init */
    int empty_semid;
    empty_semid = semget((key_t)KEY, 1, PERMISSION | IPC_CREAT | IPC_EXCL);
    if(empty_semid == -1 && errno == EEXIST) {
        printf("Specified semaphore existed and we will use it\n");
        empty_semid = semget((key_t)KEY, 1, PERMISSION);
        if(empty_semid == -1){
            perror("semget");
            detach_shm(shmaddr);
            // free_shm(shmid);
            goto FREE_SHM;
            exit(EXIT_FAILURE);
        }
    } else {
        if(empty_semid == -1) {
            perror("semget");
            detach_shm(shmaddr);
            // free_shm(shmid);
            goto FREE_SHM;
            exit(EXIT_FAILURE);
        }
        printf("created a semaphore, semid = %d\n", empty_semid);
    }
    ret = semctl(empty_semid, 0, SETVAL, 1); // set semaphore capacity as 1
    if(ret == -1){
        perror("semctl");
        detach_shm(shmaddr);
        // free_shm(shmid);
        // free_sem(empty_semid);
        goto FREE_EMPTY_SEM;
        exit(EXIT_FAILURE);
    }
    int full_semid;
    full_semid = semget((key_t)(KEY+1), 1, PERMISSION | IPC_CREAT | IPC_EXCL);
    if(full_semid == -1 && errno == EEXIST) {
        printf("Specified semaphore existed and we will use it\n");
        full_semid = semget((key_t)(KEY+1), 1, PERMISSION);
        if(full_semid == -1){
            perror("semget");
            detach_shm(shmaddr);
            // free_shm(shmid);
            // free_sem(empty_semid);
            goto FREE_EMPTY_SEM;
            exit(EXIT_FAILURE);
        }
    } else {
        if(full_semid == -1) {
            perror("semget");
            detach_shm(shmaddr);
            // free_shm(shmid);
            // free_sem(empty_semid);
            goto FREE_EMPTY_SEM;
            exit(EXIT_FAILURE);
        }
        printf("created a semaphore, semid = %d\n", full_semid);
    }
    ret = semctl(full_semid, 0, SETVAL, 0); // set semaphore capacity as 1
    if(ret == -1){
        perror("semctl");
        detach_shm(shmaddr);
        // free_shm(shmid);
        // free_sem(empty_semid);
        // free_sem(full_semid);
        goto FREE_FULL_SEM;
        exit(EXIT_FAILURE);
    }
    int N = 10;
    while(N-- > 0) {
        /* write share memory */
        if((ret = down(empty_semid)) == -1){
            perror("down");
            detach_shm(shmaddr);
            // free_shm(shmid);
            // free_sem(empty_semid);
            // free_sem(full_semid);
            goto FREE_FULL_SEM;
            exit(EXIT_FAILURE);
        }
        /*******************************************************************/
        printf("writing data to share memory......");
        int *p = (int *)shmaddr;  // access
        for(int i=0; i<SHARE_MEM_SIZE/4; i++){
            *p = (argc > 1 ? atoi(argv[1]) : 1) * i;
            p++;
        }
        sleep(5);
        printf("Done\n");
        /*******************************************************************/
        if((ret = up(full_semid)) == -1){
            perror("up");
            detach_shm(shmaddr);
            // free_shm(shmid);
            // free_sem(empty_semid);
            // free_sem(full_semid);
            goto FREE_FULL_SEM;
            exit(EXIT_FAILURE);
        }
    }
    /* delete resources */
FREE_FULL_SEM:
    free_sem(full_semid);
FREE_EMPTY_SEM:
    free_sem(empty_semid);
FREE_SHM:
    free_shm(shmid);
    return 0;
}

void detach_shm(void *shmaddr){
    shmdt(shmaddr);
}
void free_shm(int shmid){
    shmctl(shmid, IPC_RMID, NULL);
}

void free_sem(int semid){
    semctl(semid, 0, IPC_RMID);
}