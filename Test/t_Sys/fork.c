#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// int main(){
//     int pid = fork();
//     if(pid == 0){
//         printf("I am son\n");
//     }else{
//         printf("I am father\n");
//     }
//     return 0;
// }

// 不同循环，打印五个hello world
// int main(){
//     int id = fork();
//     if(id == 0){
//         printf("hello world\n");
//     }else{
//         fork();
//         fork();
//         printf("hello world\n");
//     }
//     return 0;
// }

// int main(){
//     int id[4];
//     for(int i=0; i<4; i++){
//         id[i] = fork();
//         if(id[i] == 0)
//             break;
//     }
//     printf("hello world\n");
//     printf("%d,%d,%d,%d\n", id[0], id[1], id[2], id[3]);
//     return 0;
// }



// int main(){
//     int id = vfork();
//     if(id == 0){
//         sleep(1);
//         printf("子进程:%d\n", getpid());
//         exit(0);
//     }else{
//         printf("父进程:%d\n", getpid());
//     }
//     return 0;
// }


void quit1(int status, void *ptr){
    printf("status = %d, ptr = %p\n", status, ptr);
}

int main(){
    int data = 1024;
    printf("&data = %p\n", &data);
    on_exit(quit1, &data);
    printf("main end!\n");
    return -1;
}