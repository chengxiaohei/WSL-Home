#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> count(233);

void func(int num){
    while(num-- > 0){
        count+=2;
    }
}

int main(){
    std::thread t1(func, 5000000);
    std::thread t2(func, 5000000);
    t1.join();
    t2.join();
    std::cout << count << std::endl;
    return 0;
}
