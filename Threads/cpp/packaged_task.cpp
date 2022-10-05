#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <functional>

// packaged_task方式创建的任务，并没有执行join操作，
// 如果主线程在子线程之前结束，则程序会报错:
// terminate called after throwing an instance of 'std::system_error'
//   what():  Unknown error -1
// Aborted
// 如果不像发生这样的错误，就需要将该task移动到一个thread中，然后显示调用join.

// unique function to avoid disambiguating the std::pow overload set
int f(int x, int y) { return std::pow(x,y); }

void task_lambda() {
    std::packaged_task<int(int,int)> task([](int a, int b) {
        return std::pow(a, b); 
    });
    std::future<int> result = task.get_future();
    task(2, 9);
    std::cout << "task_lambda:\t" << result.get() << '\n';
}
void task_bind() {
    std::packaged_task<int()> task(std::bind(f, 2, 11));
    std::future<int> result = task.get_future();

    task();

    std::cout << "task_bind:\t" << result.get() << '\n';
}
void task_strange(){
    std::packaged_task<int()> task(std::bind(f, 2, 11));
    task();
    std::cout << "task_bind_strange:\t" << task.get_future().get() << '\n';
}

void task_thread() {
    std::packaged_task<int(int,int)> task(f);
    std::future<int> result = task.get_future();

    std::thread task_td(std::move(task), 2, 10);
    task_td.join();

    std::cout << "task_thread:\t" << result.get() << '\n';
}

int main()
{
    task_lambda();
    task_strange();
    task_bind();
    task_thread();

    // while(1){
    //     std::this_thread::sleep_for(std::chrono::microseconds(1000));
    // }
}