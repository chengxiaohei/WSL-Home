#include <iostream>

struct Person{
	int age;
	int num;
	int id;
};
int func1(Person p){
	int temp = 1;
	return 0;
}

int func2(Person *p){
	int temp = 2;
	p->age = 1;
	return 0;
}

int func3(Person &p){
	int temp = 2;
	p.age = 1;
	return 0;
}

int main(){
	Person person;
	func1(person);
	func2(&person);
	func3(person);
	return 0;
}
