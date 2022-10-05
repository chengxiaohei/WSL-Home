#include <iostream>
#include <condition_variable>
#include <deque>
#include <thread>

std::condition_variable cv_p;
std::condition_variable cv_c;
std::mutex mtx;

void producter(std::deque<int> &car){
    static int count = 0;
    while(true){
        std::unique_lock<std::mutex> lk(mtx);
        while(!car.empty()){
            cv_p.wait(lk);
        }
        car.push_back(count++);
        lk.unlock();
        cv_c.notify_one();
    }
}

void consumer(std::deque<int> &car){
    while(true){
        std::unique_lock<std::mutex> lk(mtx);
        while(car.empty()){
            cv_c.wait(lk);
        }
        std::cout << car.front() << std::endl;
        car.pop_front();
        lk.unlock();
        cv_p.notify_one();
    }
}

int main(){
    std::deque<int> car;
    std::thread t0(producter, std::ref(car));
    std::thread t1(producter, std::ref(car));
    std::thread t2(consumer, std::ref(car));
    std::thread t3(consumer, std::ref(car));
    t0.join();
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
