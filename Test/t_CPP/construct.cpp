#include <iostream>
#include <string>
#include <unistd.h>
#include <cstring>
typedef struct {
	std::string device;
	std::string time;
	std::string ywBfb;
	std::string ywTp;
	int ywZcxh;
} Oil_Level_t;


class Test
{
public:
	Test(){
//		this->info.device = new std::string();
//		this->info.time = new std::string();
//		this->info.ywBfb = new std::string();
//		this->info.ywTp = new std::string();
//		this->info.ywZcxh = 0;

		this->info.device = "o_device1";
		this->info.time = "2018";
		this->info.ywBfb = "20";
		this->info.ywTp= "string.jpg";
		this->info.ywZcxh = 0;
	}
	~Test(){
		//delete this->info.device;
		//delete this->info.time;
		//delete this->info.ywBfb;
		//delete this->info.ywTp;
	}
	void showOil(){
		std::cout << info.device << std::endl;
		std::cout << info.time << std::endl;
		std::cout << info.ywBfb << std::endl;
		std::cout << info.ywTp<< std::endl;
		std::cout << info.ywZcxh<< std::endl;
	}
	Oil_Level_t info;
};

int main(){
{
	Test *t = new Test();
	t->showOil();
	delete t;
}
	return 0;
}

