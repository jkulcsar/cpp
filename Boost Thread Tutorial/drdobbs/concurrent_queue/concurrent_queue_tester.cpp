
#include "concurrent_queue.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/limits.hpp>

#include <boost/ref.hpp>

#include <boost/thread/xtime.hpp>

#include <iostream>
#include <string>

#include <time.h>

boost::mutex io_mutex;

//
// based on:
// http://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html
//


template<typename T>
class producer_type {
public:

	producer_type() {}
	
	void operator()(concurrent_queue<T>& q, 
			boost::condition_variable& queue_status, 
			boost::mutex& queue_status_mutex,
			boost::mutex& is_done_mutex,
			bool& is_done_flag
			) {
		{
			boost::mutex::scoped_lock lock(io_mutex);
			std::cout << "Producer thread running..." << std::endl;
		}

		try
		{
				for(short i = 0; i < 100 /*std::numeric_limits<short>::max()*/; ++i) {
					T elem = boost::lexical_cast<T>(i);
					{
						boost::mutex::scoped_lock lock(io_mutex);
						std::cout << "Produced: " << "\t" << boost::lexical_cast<T>(i)<< std::endl;
					}

					q.push(elem);
				}

		}
		catch( std::ios_base::failure ex )	{
			std::cout << ex.what();
		}
		catch( std::runtime_error re )	{
			std::cout << re.what();
		}

		boost::unique_lock<boost::mutex> lock(is_done_mutex);		
		is_done_flag = true;
		lock.unlock();
		{
			boost::mutex::scoped_lock lock(io_mutex);
			std::cout << "Producer thread quit:\t" << boost::this_thread::get_id() << std::endl;
		}

	}
};

template<typename T>
class consumer_type {

public:
	void operator()(concurrent_queue<T>& q, 
		boost::condition_variable& queue_status, 
		boost::mutex& queue_status_mutex,
		boost::mutex& is_done_mutex,
		bool& is_done_flag) {
		{
			boost::mutex::scoped_lock lock(io_mutex);
			std::cout << "Consumer thread is running..." << std::endl;
		}

		boost::unique_lock<boost::mutex> lock(is_done_mutex);
		bool done = is_done_flag;
		lock.unlock();

		while(!done) {
			T elem;
			q.wait_and_pop(elem);
			//if(q.try_pop(elem))
			{
				boost::mutex::scoped_lock lock(io_mutex);
				std::cout << "Consumed: " << "\t" << elem << " by \t " << boost::this_thread::get_id() << std::endl;
			}
		
			boost::unique_lock<boost::mutex> lock(is_done_mutex);
			done = is_done_flag;
			lock.unlock();

		}

		{
			boost::mutex::scoped_lock lock(io_mutex);
			std::cout << "Consumer thread quit!" << std::endl;
		}

	}
};

template<typename T>
class manager {

	// shared queue of type T elements
	concurrent_queue<T> q_;
	
	// add a flag and a mutex for sync,
	// flagging when the producer is done; each consumer thread
	// should quit after the queue is empty
	// 
	boost::mutex is_done_mutex_;
	bool is_done_flag_;

	//
	boost::condition_variable queue_status_;
	boost::mutex queue_status_mutex_;

	producer_type<T> producer_object_;
	consumer_type<T> consumer_object_;

	boost::thread producer_thread_;
	boost::thread consumer_thread_;
	boost::thread_group consumer_thread_group_;

public:
	manager() : is_done_flag_(false) {
		producer_thread_ = boost::thread(producer_object_, 
			boost::ref<concurrent_queue<T> >(q_),
			boost::ref<boost::condition_variable>(queue_status_),
			boost::ref<boost::mutex>(queue_status_mutex_),
			boost::ref<boost::mutex>(is_done_mutex_),
			boost::ref<bool>(is_done_flag_)
			);
		consumer_thread_ = boost::thread(consumer_object_, 
			boost::ref<concurrent_queue<T> >(q_),
			boost::ref<boost::condition_variable>(queue_status_),
			boost::ref<boost::mutex>(queue_status_mutex_),
			boost::ref<boost::mutex>(is_done_mutex_),
			boost::ref<bool>(is_done_flag_)
			);
		    
		for (int i = 0; i < 2; ++i)
			consumer_thread_group_.add_thread(
				new boost::thread(consumer_object_, 
				boost::ref<concurrent_queue<T> >(q_),
				boost::ref<boost::condition_variable>(queue_status_),
				boost::ref<boost::mutex>(queue_status_mutex_),
				boost::ref<boost::mutex>(is_done_mutex_),
				boost::ref<bool>(is_done_flag_))
				);




		consumer_thread_.join();
		consumer_thread_group_.join_all();
		producer_thread_.join();
	}
};


int main(int argc, char** argv) {
	
	//
	// seed the random number generator
	srand( (unsigned)time( NULL ) );

	manager<std::string> manager_object;

	return 0;
}
