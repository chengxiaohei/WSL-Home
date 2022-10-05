#include <iostream>
#include <string>
using namespace std;

class Person{
public:
    Person(char const *name, int age){
        cout << "我自己定义的普通构造函数" << endl;
        this->name = new string(name);
        this->age = new int(age);
    }
    // Person(Person &other) = default;  //这是默认的赋值构造器
    Person(const Person &other){
        cout << "我自己定义的拷贝构造函数" << endl;
        this->name = new string(other.name->data());
        this->age = new int(*(other.age));
    }
    Person(Person &&other){
        cout << "我自己定义的右值引用拷贝构造函数" << endl;
        this->name = other.name;
        this->age = other.age;
        other.name = nullptr;
        other.age = nullptr;
    }
    // 赋值运算符重载
    Person &operator= (const Person &other) {
        cout << "我自己定义的=运算符重载" << endl;
        if(this != &other){
            delete this->name;
            this->name = new string(other.name->data());
            *(this->age) = other.getAge();
        }
        return *this;
    }
    Person &operator= (Person &&other){
        cout << "我自己定义的右值引用=运算符重载" << endl;
        if(this != &other){
            if(this->name != nullptr) delete this->name;
            if(this->age != nullptr) delete this->age;
            this->name = other.name;
            this->age = other.age;
            other.name = nullptr;
            other.age = nullptr;
        }
        return *this;
    }
    ~Person(){
        cout << "析构函数" << endl;
        delete this->name;
        delete this->age;
    }

    const char *getName() const {
        return (*(this->name)).data();
    }
    int getAge() const {
        return *(this->age);
    }
    void chageAge(int newAge){
        *(this->age) = newAge;
    }
private:
    string* name;
    int *age;
};

ostream &operator<<(ostream &os, Person const &person){
    return os << "Person(" << person.getName() << "," << person.getAge() << ")";
}

int main(){
    Person p1("jack", 11);
    Person p2("??", 0);
    p2 = std::move(p1);
}
