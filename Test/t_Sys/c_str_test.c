#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

const char *str = "0x1124 532 452";

int main(){
	char str1[] = "hel";
	char str2[100] = "aaaaahellobbbbb";
	char *str3 = strstr(str2, str1);
	printf("%s", str3);
	size_t a = strcspn(str1, str2);
	printf("a:%ld", a);
	return 0;
}