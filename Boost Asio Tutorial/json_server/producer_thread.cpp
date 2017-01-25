
#include "producer_thread.hpp"

void producer_thread(
	boost::condition_variable& condition_go_produce, 
	boost::mutex& go_produce_mutex) {

//	boost::unique_lock<boost::mutex> lock(go_produce_mutex);
//	condition_go_produce.wait(lock);

	try {

	}
	catch( std::ios_base::failure ex )	{
		std::cout << ex.what();
	}
	catch( std::runtime_error re )	{
		std::cout << re.what();
	}
}
