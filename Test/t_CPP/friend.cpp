#include <iostream>

class A{
private:
	int a = 0;
	int b = 0;
public:
	void func(A &aa){
		aa.a = 1;
	}
	void show(){
		std::cout << a << " " << b << std::endl;
	}
};


int main(){
	A t1;
	A t2;
	t1.func(t2);
	t1.show();
	t2.show();
	return 0;
}

