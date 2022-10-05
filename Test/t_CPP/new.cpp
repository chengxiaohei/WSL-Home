#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>

using namespace std;

class A
{
public:
	vector<int> V;
};

int main(){
	A a;
	a.V.push_back(1);
	std::cout << a.V.size() << std::endl;

	return 0;
}
