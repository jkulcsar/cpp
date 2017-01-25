
#include <iostream>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio.hpp>

int main(int argc, char** argv) {

	boost::asio::io_service io;

	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
	t.wait();

	std::cout << "Synchronous timer expired!" << std::endl;

	return 0;
}