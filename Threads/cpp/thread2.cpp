#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

int Count = 0;
std::mutex mtx;


void func1(int n){
    while(n-- > 0){
        std::lock_guard<std::mutex> lk(mtx);  //当lk创建时对mtx加锁，当离开作用域时进行解锁
        Count++;
    }
}

void func2(int n){
    while(n-- > 0){
        std::unique_lock<std::mutex> lk(mtx); // 与lock_guard相比，添加了一些成员函数，可以在离开作用域之前手动释放锁
        Count++;
        std::cout << lk.owns_lock() << std::endl;
        lk.unlock();
    }
}

int main(){
    std::thread t1(func2, 100000);
    std::thread t2(func2, 100000);
    t1.join();
    t2.join();
    // std::this_thread::sleep_for(std::chrono::microseconds(1000));
    std::cout << Count << std::endl;
    return 0;
}