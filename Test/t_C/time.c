#include <stdio.h>
#include <time.h>
#include <sys/time.h>


int main(){
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);

    printf("%d,%d\n", tv.tv_sec, tv.tv_usec);

    time_t tx;
    time(&tx);
    printf("%d\n", tx);
    return 0;
}