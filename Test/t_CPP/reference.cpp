#include <iostream>
#include <vector>

int main(){
	std::vector<int> v(100, 1);
	for(auto &&i : v){
		std::cout << i << " ";
	}
	std::cout << std::endl;
	return 0;
}
