#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>

#define SEMKEY 141L
#define PERMS 0666

int semid = -1;
int res = -1;

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

static void deleteSem(){
    printf("delete sem\n");
    res = semctl(semid, 0, IPC_RMID);
    if(res == -1){
        perror("semctl");
        exit(EXIT_FAILURE);
    }
}

void init_sem()
{
    semid=semget(SEMKEY, 0, IPC_CREAT | PERMS); //寻找现有信号量
    if(semid == -1)
    {
        printf("create semaphore\n");
        semid=semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | PERMS); //创建新的,唯一的信号量
        if(semid == -1)
        {
            printf("couldn't create semaphore\n");
            exit(EXIT_FAILURE);
        }
        // res=semctl(semid, 0, SETVAL, 1); //设置信号量容量
        union semun sem_union;
        sem_union.val = 2;  // 设定信号量容量
        res=semctl(semid, 0, SETVAL, sem_union); //设置信号量容量
        if(res == -1){
            perror("semctl");
            exit(EXIT_FAILURE);
        }
        atexit(deleteSem);
    }
}
void down()
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1;
    sem_b.sem_flg = SEM_UNDO;
    res=semop(semid, &sem_b, 1);
}

void up()
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;
    res=semop(semid, &sem_b, 1);
}


int main(int argc, char *argv[])
{
    init_sem();
    printf("before critical code\n");
    down();
    printf("in critical code\n");
    sleep(10);
    up();
    printf("out of critival code\n");
    return 0;
}