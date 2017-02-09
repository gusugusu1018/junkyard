#include <iostream>
#include <string>
#include <sstream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main(int argc, char** argv)
{
	boost::asio::io_service io_service;
	udp::resolver resolver(io_service);
	udp::resolver::query query(udp::v4(), "127.0.0.1", "12345");
	udp::endpoint receiver_endpoint = *resolver.resolve(query);

	udp::socket socket(io_service);
	socket.open(udp::v4());

	//send float data
	float num = 1.0;
	for (int i=0; i<5; i++) {
		std::string str;
		str = std::to_string(num);
		str.push_back(' ');
		str += std::to_string(num+100);
		str.push_back(' ');
		str += std::to_string(num+2000);
		std::cout << "send : " << num << std::endl;
		socket.send_to(boost::asio::buffer(str), receiver_endpoint);
		num++;
	}
	return 0;
}

