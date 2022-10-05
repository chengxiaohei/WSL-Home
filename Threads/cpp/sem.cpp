#include <iostream>
#include <thread>
#include <semaphore>  // since c++20
#include <queue>

std::counting_semaphore<3> cSem_for_producter(3);
std::counting_semaphore<3> cSem_for_consumer(0);
std::counting_semaphore<3> cSem(3);

// binary_semaphore是counting_semaphore的特化版本
// 相当于容量为1的信号量，
// 也就是相当于互斥量与条件变量的结合
std::binary_semaphore bSem_for_producter(1);
std::binary_semaphore bSem_for_consumer(0);

std::queue<int> Q;

void producter() {
	static int count = 0;
	while (true) {
		cSem_for_producter.acquire();
		Q.push(count++);
		cSem_for_consumer.release();
	}
}

void consumer() {
	while (true) {
		cSem_for_consumer.acquire();
		std::cout << Q.front() << std::endl;
		Q.pop();
		cSem_for_producter.release();
	}
}

void func() {
	while (true) {
		cSem.acquire();
		std::cout << std::this_thread::get_id() << ": do something" << std::endl;
		cSem.release(2);
	}
}


int main() {
	std::thread t1(producter);
	std::thread t2(consumer);
	std::thread t3(consumer);
	std::thread t4(producter);
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	//std::thread t1(func);
	//std::thread t2(func);
	//std::thread t3(func);
	//std::thread t4(func);
	//t1.join();
	//t2.join();
	//t3.join();
	//t4.join();
	return 0;
}