#include <iostream>

void func(){
	static int a = 0;
	int b = 1;
	a += 1;
	std::cout << a << std::endl;
	std::cout << &a << std::endl;
	std::cout << b << std::endl;
	std::cout << &b << std::endl;
}

int main(){
	func();
	func();
	func();
	return 0;
}
