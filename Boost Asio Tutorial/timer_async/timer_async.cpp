
#include <iostream>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

class printer {
	int count_;
	boost::asio::deadline_timer timer_;

public:
	printer(boost::asio::io_service& io) : timer_(io, boost::posix_time::seconds(1)),  count_(0) {
		timer_.async_wait(boost::bind(&printer::print, this));
	}

	~printer() {
		std::cout << "Printer says final count is " << count_ << std::endl;
	}

	void print() {
		if (count_ < 5) {
			std::cout << "Printer counts: " << count_ << "\n";
			++count_;

			timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
			timer_.async_wait(boost::bind(&printer::print, this));
		}
	}
};


void print(const boost::system::error_code& /*e*/,
		   boost::asio::deadline_timer* t,
		   int* count) {
   if(*count < 5) {
	   std::cout << "Callback called at count: " << *count << std::endl;
	   ++(*count);
	   t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
	   t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, count));
   }
}

int main(int argc, char** argv) {

	boost::asio::io_service io;
	int count = 0;

	boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));

	t.async_wait(boost::bind(print, boost::asio::placeholders::error, &t, &count));

	//t.async_wait(print);
	//std::cout << "Waiting for async callback..." << std::endl;
	
	printer p(io);
	io.run();
	
	std::cout << "Final count is: " << count << std::endl;
	
	return 0;
}

