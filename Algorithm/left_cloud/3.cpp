#include <iostream>
#include <unordered_set>
#include <algorithm>

struct Info{
    int a;
    int b;
    int c;
};

Info func(int a, int b, int c){
    return Info{1,2,3};
}

int main(int argc, char const *argv[]){
    std::cout << func(1,2,3).a << std::endl;
    return 0;
}