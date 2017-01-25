
#include <iostream>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

class printer {
	boost::asio::strand strand_;
	boost::asio::deadline_timer timer1_;
	boost::asio::deadline_timer timer2_;
	int count_;

public:

	// An boost::asio::strand guarantees that, for those handlers that are dispatched 
	// through it, an executing handler will be allowed to complete before the next 
	// one is started. This is guaranteed irrespective of the number of threads 
	// that are calling io_service::run().
	// Of course, the handlers may still execute concurrently with other handlers 
	// that were not dispatched through an boost::asio::strand, or were dispatched 
	// through a different boost::asio::strand object. 
	//
	printer(boost::asio::io_service& io) : 
	  timer1_(io, boost::posix_time::seconds(1)),
	  timer2_(io, boost::posix_time::seconds(1)),
	  strand_(io),
	  count_(0) {

		  timer1_.async_wait(strand_.wrap(boost::bind(&printer::print1, this)));
		  timer2_.async_wait(strand_.wrap(boost::bind(&printer::print2, this)));
	}

	~printer() {
		std::cout << "Printer says final count is " << count_ << std::endl;
	}

	void print1() {
		if (count_ < 10) {
			std::cout << "Timer1 in Printer counts: " << count_ << "\n";
			++count_;

			timer1_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
			timer1_.async_wait(strand_.wrap(boost::bind(&printer::print1, this)));
		}
	}

	void print2() {
		if (count_ < 10) {
			std::cout << "Timer2 in Printer counts: " << count_ << "\n";
			++count_;

			timer2_.expires_at(timer2_.expires_at() + boost::posix_time::seconds(1));
			timer2_.async_wait(strand_.wrap(boost::bind(&printer::print2, this)));
		}
	}
};



int main(int argc, char** argv) {

	boost::asio::io_service io;

	printer p(io);

	// The main function now causes io_service::run()  to be called from two threads: 
	// the main thread and one additional thread.
	// This is accomplished using an boost::thread object. 
	//
	boost::thread t(boost::bind(&boost::asio::io_service::run, &io));
	io.run();
	t.join();
	
	return 0;
}
