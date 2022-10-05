#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	int oldoutfd = dup(1);
	int filefd = open("tmp", O_WRONLY | O_CREAT, 0666);
	dup2(filefd, 1);
	printf("hello\n");
	fflush(stdout);
	dup2(oldoutfd, 1);
	printf("hello\n");
	close(filefd);
	return 0;
}
