#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	pid_t cpid;
	int pipefd[2];
	char buf;

	if(argc != 2) {
		fprintf(stderr, "Usage: %s <strint>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if(pipe(pipefd) == -1) {  // create pipe
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid = fork();
	if(cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if(cpid == 0){
		printf("child process!\n");
		close(pipefd[1]);
		while(read(pipefd[0], &buf, 1) > 0)  // read 1 char from pipefd[0] into &buf
		{
			sleep(1);
			write(STDOUT_FILENO, &buf, 1);
		}
		while(STDOUT_FILENO, "\n", 1);
		close(pipefd[0]);
		_exit(EXIT_SUCCESS);
	}else{
		printf("father process!\n");
		close(pipefd[0]);
		write(pipefd[1], argv[1], strlen(argv[1]));
		close(pipefd[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
	return 0;
}
