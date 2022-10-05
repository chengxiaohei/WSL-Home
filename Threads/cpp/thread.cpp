#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

int Count = 0;
std::mutex mtx;


void func1(int n){
    while(n-- > 0){
        mtx.lock();
        Count++;
        mtx.unlock();
    }
}

int main(){
    std::thread t1(func1, 100000);
    std::thread t2(func1, 100000);
    t1.join();
    t2.join();
    // std::this_thread::sleep_for(std::chrono::microseconds(1000));
    std::cout << Count << std::endl;
    return 0;
}