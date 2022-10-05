#include <stdio.h>
#include <string.h>
int main(){
	char str[] = "abcdefg";
	int N = strlen(str);
	for(int i=0; i<N/2; i++){
		char temp = str[i];
		str[i] = str[N-1-i];
		str[N-1-i] = temp;
	}
	printf("%s\n", str);
	return 0;
}
