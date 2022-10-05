#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>

#define KEY 14
#define SHARE_MEM_SIZE (4096 * 10)

int main(){
    int ret;
    int shmid;
    shmid = shmget((key_t)KEY, SHARE_MEM_SIZE, 0666);
    if(shmid == -1){
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    void *shmaddr = shmat(shmid, NULL, SHM_RDONLY);  // attach
    if(shmaddr == (void *) -1){
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    int *p = (int *)shmaddr;  // access
    for(int i=0; i<SHARE_MEM_SIZE/4; i++){
        printf("%d\t", *p);
        p++;
    }
    ret = shmdt(shmaddr);  // detach 
    if(ret == -1){
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    return 0;
}