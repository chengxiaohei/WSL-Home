#include <stdio.h>


typedef float (* returnType)(int);
typedef int listType[200];
typedef float funcType(int);

returnType func(int a, int b, float c){
	return (returnType)0;
}

funcType *func2(int a, int b, float c){
	return (returnType)0;
}

int main(){
	float (*(*fp2)(int, int, float))(int);
	fp2 = func;
	fp2 = func2;
	listType a;
	for(int i=0; i<200; i++){
		a[i] = i;
	}
	printf("%d\n", typeof(returnType) == typeof(funcType *));
	return 0;
}
