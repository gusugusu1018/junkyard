#include <boost/thread.hpp>
#include <iostream>
 
void
saysl() {
	for (int i=0;i<10;i++) {
		std::cout << "sl" << std::endl;
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	}
}
void
sl() {
	while(1) {
		system("sl");
		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
	}
}
int
main(int argc, char const* argv[])
{
        boost::thread th1(saysl);
        boost::thread th2(sl);
	th1.join();
	th2.interrupt();
	sleep(6); 
        return 0;
}
