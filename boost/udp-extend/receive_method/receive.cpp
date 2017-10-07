// Yuji Ogusu
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>

using boost::asio::ip::udp;
//Prototype Declaraion
void udp_receive_thread(void );

struct fVector3
{
	double m_x;
	double m_y;
	double m_z;
};

class udp_receiver
{
	public:
		udp_receiver(boost::asio::io_service& io_service)
			: socket_(io_service, udp::endpoint(udp::v4(), UDP_PORT))
		{
			//constructor starts receiver
			start_receive();
		}

		// getter of the property
		void getData(fVector3* pPos) {
			pPos->m_x = vPos.m_x;
			pPos->m_y = vPos.m_y;
			pPos->m_z = vPos.m_z;
		}

	private:
		const static int UDP_PORT = 12345;
		udp::socket socket_;
		udp::endpoint remote_endpoint_;

		boost::array<char,512> recv_buf;

		void start_receive() {
			socket_.async_receive_from(
					boost::asio::buffer(recv_buf), remote_endpoint_,
					boost::bind(&udp_receiver::handle_receive, this,
						boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
			// Waitting for event
			//std::cout << "Waitting" << std::endl;
		}

		void handle_receive(const boost::system::error_code& error, size_t len) {
			if (!error || error == boost::asio::error::message_size){
				std::string message(recv_buf.data(), len);
				//any function;
				// show message on terminal
				// std::cout << message << std::endl; // all message
				this->receive_data(message); //example// getter of the property

				start_receive();
			}
		}
		// Property of the Vehicle position
		fVector3 vPos;

		// setter of the property
		void receive_data(std::string strData) {
			std::vector<std::string> data_str(3);
			boost::split(data_str, strData, boost::is_space()); // data constructor // x y z
			vPos.m_x = std::atoi(data_str[0].c_str());
			vPos.m_y = std::atoi(data_str[1].c_str());
			vPos.m_z = std::atoi(data_str[2].c_str());
			//show the property
			std::cout << "x :" << vPos.m_x << " y :" << vPos.m_y << " z :" << vPos.m_z << std::endl;
		}
};

void udp_receive_thread() {
	try {
		boost::asio::io_service io_service;
		udp_receiver receiver(io_service);
		io_service.run();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

int main()
{
	// init thread
	boost::thread thr_udp(&udp_receive_thread);
	while (1)
	{

	}

	return 0;
}


