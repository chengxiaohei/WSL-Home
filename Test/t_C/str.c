#include <stdio.h>


int main(){
	char a[] = "hello";
	char *b = "hello";
	char c[6] = "hello";
	printf("%p\n", a);
	printf("%p\n", b);
	printf("%p\n", c);
	return 0;
}
