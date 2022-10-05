#include <iostream>
#include <thread>
#include <future>


int func1(int a, int b){
    int ret_a = a * a;
    int ret_b = b * 2;
    return ret_a + ret_b;
}


int main(){
    std::future<int> f = std::async(func1, 1, 2);  //异步地去调用函数，保证在调用f.get前，函数执行结束
    std::async(std::launch::async, func1, 1, 2);  // 新建一个新线程执行函数
    std::async(std::launch::deferred, func1, 1, 2);  // 延后执行，不会创建新的线程
    //async默认情况下，编译器会帮我们选一个
    
    std::cout << f.get() << std::endl;
    std::cout << f.get() << std::endl;
    std::cout << f.get() << std::endl;
    std::cout << f.get() << std::endl;
    std::cout << f.get() << std::endl;
    std::cout << f.get() << std::endl;
}
