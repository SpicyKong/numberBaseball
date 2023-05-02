#include <iostream>
#include <stdlib.h>
#include <thread>
using std::thread;

void func1() {
    std::string a;
	for (int i = 0; i < 10; ++i) {
		std::cin >> a;
		std::cout << a << "\n";
        //std::cout << "\33[2K\r" << a << "\n";
	}
}

void func2() {
	while(1) {
		std::cout << "hello~! \n";
        _sleep(1000);
	}
}

void func3() {
	for (int i = 0; i < 10; ++i) {
		std::cout << "쓰레드 3 작동중! \n";
	}
}


int main() {

	thread t1(func1);
	thread t2(func2);

	t1.join();
	t2.join();
}