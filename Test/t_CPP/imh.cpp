#include <iostream>
using namespace std;
class A 
{
public:
	void print()
	{
	  cout << "A" << endl;
	}
private:
	long long a;
};

class B : protected A
{
public:
	void pp(){
		print();
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
	b.pp();
	return 0;
}

