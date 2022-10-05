#include <stdlib.h>
#include <unistd.h>
void func(void){
	char *buff = (char*)malloc(10);
}

int main(){
	func();
	while(1){
		sleep(1);
	}
	char *x = (char*)malloc(10);
	return 0;
}

