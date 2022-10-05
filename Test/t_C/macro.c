#include <stdio.h>

struct test{
	struct test *next;
};

struct Test{
	int a;
	char b;
	struct test t;
	int *c;
};

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

// Test: 上层结构体的名称
// c: 本层结构体字段名字
//#define container_of(Test, c) ((struct Test *)((&c)-(&(((struct Test *)0)->#c))))

#define container_of(ptr, type, member) \
	(type *)((char *)ptr - offsetof(type, member))
	
//#define func(a,b) a##b

#define func(c) \
	func_##c()

int func_a(){
	printf("a\n");
}

int func_b(){
	printf("b\n");
}

#define func1(c) printf(#c ": %d\n", c)
#define add_show(a,b) \
	printf(#a " + " #b " = %d\n", a+b);

#define PR(...) printf(__VA_ARGS__)

#define PRM(a, ...) printf("prefix: " #a ": %d , " __VA_ARGS__, a) 

#define TRACE(S) (printf("%s\n", #S), S);

int main(){
	//struct Test T;
	//struct test t;
	//printf("offsetof a: %ld\n", offsetof(struct Test, a));
	//printf("offsetof b: %ld\n", offsetof(struct Test, b));
	//printf("offsetof t: %ld\n", offsetof(struct Test, t));
	//printf("offsetof c: %ld\n", offsetof(struct Test, c));
	//struct Test *T1 = container_of(&T.t, struct Test, t);
	//printf("%d\n", &T == T1);
	//func(a);
	//func(b);
	//int x = 110;
	//func1(x);
	//int y = 1, z = 2;
	//add_show(y,z);
	//PR("hello:%d\n", 11);
	//
	//PRM(x, "hello %s: %d\n", "world", 120);

	//printf("prefix: x: %d , hello %s: %d\n", "world", 120, 110);

	int xx = 1;
	int b = TRACE(xx);
	return 0;
} 
