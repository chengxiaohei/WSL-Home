#include <iostream>
using namespace std;
class A 
{
public:
	void virtual print()
	{
	  cout << "A" << endl;
	}
private:
	long long a;
};

class B : public A
{
public:
	void print()
	{
		cout << "B" << endl;
	}
};

class C : public B
{
public:
	void print(){
		cout << "C" << endl;
	}
private:
	int a = 0;
};

int main()
{
	B b;
	A a = (B)b;
	a.print();
	A *pa = new B();
	pa->print();
	int data[10];
	cout << data[1000000] << endl;
	return 0;
}

