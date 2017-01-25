
#include "boost/thread/thread.hpp"
#include "boost/thread/mutex.hpp"
#include <iostream>

boost::mutex io_mutex;

struct count
{
	count(int id) : id(id) {}
	void operator()()
	{
		for(int i=0; i<100; ++i)
		{
			boost::mutex::scoped_lock lock(io_mutex);
			std::cout << id << " : " << i << std::endl;
		}
	}

	int id;
};

void hello()
{
	std::cout << "I'm a thread." << std::endl;
}

int main(int argc, char** argv)
{
//	boost::thread thrd(&hello);
	boost::thread thrd;
	thrd = boost::thread( hello );

	boost::thread counter1(count(1));
	boost::thread counter2(count(2));
	thrd.join();

	counter1.join();
	counter2.join();

	return 0;
}
