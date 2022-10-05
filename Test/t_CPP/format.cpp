#include <iostream>
#include <format>
#include <cassert>
int main(){
	std::string message = std::format("The answer is {}.", 42);
	assert( message == "The answer is 42.");
	return 0;
}
