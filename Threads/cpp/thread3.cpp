#include <iostream>
#include <thread>

int main(){
    int a = 1, b = 2, c = 0;
    std::thread t1(
        [](int a, int b, int &c){c = a + b;}, a, b, std::ref(c)
    );
    t1.join();
    std::cout << c << std::endl;
    return 0;
}