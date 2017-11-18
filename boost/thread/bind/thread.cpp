#include <iostream>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
using namespace std;
using namespace boost;

const int kCount =  100000000;
const int kInterval = 1000000;

void PrintString(const char *str) {
	for(int i = 0; i != kCount; ++i)
		if (!(i % kInterval)) cout << str;
}

int main() {
	const char *kHello = "Hello ";
	const char *kWorld = "World! ";

	thread thr_hello(bind(&PrintString, kHello));
	thread thr_world(bind(&PrintString, kWorld));

	thr_hello.join();
	thr_world.join();
	return 0;
}
