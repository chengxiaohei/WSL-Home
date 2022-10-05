#include "mysem.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


int down(int semid)
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1;
    sem_b.sem_flg = SEM_UNDO;
    return semop(semid, &sem_b, 1);
}

int up(int semid)
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;
    return semop(semid, &sem_b, 1);
}