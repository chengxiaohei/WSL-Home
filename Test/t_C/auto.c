#include <stdio.h>


int main(){
	auto int a = 1;
	register int b = 2;
	static int c = 3;
	printf("&a = %p\n", &a);
	//printf("&b = %p\n", &b);
	printf("&c = %p\n", &c);
	return 0;
}
