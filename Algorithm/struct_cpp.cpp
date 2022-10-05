#include <iostream>

struct A{
    int a;
    int b;
    int c;
    A(): a(11), b(22), c(33){};
    A(int a, int b, int c): a(a), b(b), c(c){};
};

int main(int argc, char *argv[]){
    A at;
    std::cout << at.a << std::endl;
    std::cout << at.b << std::endl;
    std::cout << at.c << std::endl;
    std::cout << sizeof(A) << std::endl;
    return 0;
}