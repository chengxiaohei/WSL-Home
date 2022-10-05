#include <stdio.h>
#include <string>
#include <vector>
#include <cstring>

int main(){
	int data[] = {1,2,3,4,5,6,7,7};
	int length = sizeof(data)/sizeof(int);
	int *data2 = (int *)malloc(length * sizeof(int));
	int *data3 = new int[8]{1,2,3,4,5,6,7,7};
	std::vector<int> *data4 = new std::vector<int>(5,3);

	char str[] = "hello";
	char *str2 = (char *)malloc(6);
	memset(str2, 'A', 5);
	char *str3 = new char[6]{'h','e','l','l','o'};
	std::string *str4 = new std::string("hello");
	
	return 0;
}

