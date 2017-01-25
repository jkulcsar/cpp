
#include <boost/thread/thread.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>    

void producer_thread(
	boost::condition_variable& , 
	boost::mutex&
	);

