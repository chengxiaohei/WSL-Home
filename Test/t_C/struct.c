#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
struct Test
{
	//char a;
	unsigned int b:1;
	//unsigned int c:1;
	//char d:1;
	//unsigned char e:1;
	int x;
	bool f:1;

	//long f:1;
	//unsigned long g:1;
	//long long h:1;
	//unsigned long long i:1;
};

struct HH{
	bool a;
	bool b;
	bool c;
};

struct FF{
	int a;
	int b[];
};

int main(){
	printf("%ld\n", sizeof(struct FF));
	struct FF *f = (struct FF*)malloc(16);
	f->a = 0;
	f->b[0] = 1;
	f->b[1] = 2;
	f->b[2] = 3;
	printf("%ld\n", sizeof(*f));
	return 0;
}

