#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>


void func1(int a, int b, std::promise<int> &p){
    int ret_a = a * a;
    int ret_b = b * 2;
    p.set_value(ret_a + ret_b);
}
// func2要使用func1运算结果
void func2(std::future<int> &f, int &res){
    res = f.get() * 2;
}

int main(){
    int res = 0;
    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::thread t1(func1, 1,2, std::ref(p));
    std::thread t2(func2, std::ref(f), std::ref(res));
    t1.join();
    t2.join();
    std::cout << res << std::endl;
    return 0;
}