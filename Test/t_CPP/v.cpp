#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]){

	while(1);
	vector<int> vecNum{3,1,2,3,5,4};
	auto iter = vecNum.begin()+2;
	vecNum.erase(iter);
	iter = vecNum.begin();
	while(iter != vecNum.end())
	{
		std::cout << *iter << "\t" ;		
		iter++;
	}
	std::cout << std::endl;

	return 0;

}
