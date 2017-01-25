
#include "../concurrent_queue/concurrent_queue.hpp"
#include <boost\shared_ptr.hpp>

boost::mutex io_mutex;

class A {
public:
	void operator()()
	{
		boost::mutex::scoped_lock lock(io_mutex);
		std::cout << "A" << std::endl;
	}
	void operator()(int i)
	{
		boost::mutex::scoped_lock lock(io_mutex);
		std::cout << "A:" << i << std::endl;
	}
};

class B {
public:
	void operator()()
	{
		boost::mutex::scoped_lock lock(io_mutex);
		std::cout << "B" << std::endl;
	}
};


int main( int argc, char** argv )
{
	// create two queues of different types
	//
	concurrent_queue< boost::shared_ptr<A> > conqA;
	concurrent_queue< boost::shared_ptr<B> > conqB;

	for( int i=0; i<10; ++i)
	{
		conqA.push( boost::shared_ptr<A>(new A()) );
		conqB.push( boost::shared_ptr<B>(new B()) );
	}

	int counter = 0;
	while( !conqA.empty() )
	{
		boost::shared_ptr<A> elemA;
		boost::shared_ptr<B> elemB;
		conqA.try_pop( elemA );
		conqB.try_pop( elemB );
//		(*elemA)();
//		(*elemA)(counter);
		boost::thread t1(*elemA);
		boost::thread t2(*elemA, boost::ref<int>(counter) );
		boost::thread t3(*elemB);
		t1.join();
		t2.join();
		t3.join();
		++counter;
	}

	return 0;
}

