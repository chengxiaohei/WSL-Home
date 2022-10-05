#include <stdio.h>

int x = 0;
int y = 0;
int z = 100;
int a = 200;

int main(){
	printf("x:%p\n", &x);
	printf("y:%p\n", &y);
	printf("z:%p\n", &z);
	printf("a:%p\n", &a);
	return 0;
}
