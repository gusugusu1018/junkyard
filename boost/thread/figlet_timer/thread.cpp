#include <boost/thread.hpp>
#include <iostream>
#include <string>
 
void
saysl() {
	for (int i=0;i<10;i++) {
		std::cout << "sl" << std::endl;
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	}
}
void
sl() {
	int counter=0;
	std::string command_str("figlet ");
	std::string num_str = std::to_string(counter);
	while(1) {
		system((command_str+num_str).c_str());
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		counter++;
		num_str = std::to_string(counter);
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
