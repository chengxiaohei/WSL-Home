#include <sys/times.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(){
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
	char buf[128];
	memset(buf, 0, 128);
	char *x = ctime_r(&tv.tv_sec, buf);
	assert(x == buf);
	printf("%s", ctime(&tv.tv_sec));
	printf("%s", buf);
	//struct tm *t1 = localtime(&tv.tv_sec);
	//struct tm *t2 = gmtime(&tv.tv_sec);
	struct tm t1;
	struct tm *tx = localtime_r(&tv.tv_sec, &t1);
	assert(tx == &t1);
	struct tm t2;
	struct tm *ty = gmtime_r(&tv.tv_sec, &t2);
	assert(ty == &t2);
	char buf2[32];
	char *bufx = asctime_r(tx, buf2);
	assert(buf2 == bufx);
	char buf3[32];
	char *bufy = asctime_r(ty, buf3);
	assert(buf3 == bufy);
	printf("%s", buf2);
	printf("%s", buf3);
	return 0;
}
