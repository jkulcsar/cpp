
#include "thread_safe_queue.hpp"

#include "boost/thread/thread.hpp"
#include "boost/thread/mutex.hpp"
#include "boost/thread/condition.hpp"

#include "boost/lexical_cast.hpp"
#include "boost/limits.hpp"

#include "boost/ref.hpp"

#include "boost/thread/xtime.hpp"

#include <iostream>
#include <string>

#include <time.h>

boost::mutex io_mutex;

template<typename T>
class producer_type {
public:

	producer_type() {}
	
	void operator()(thread_safe_queue<T>& q, 
			boost::condition& queue_status, 
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
			if(q.size() >= thread_safe_queue<T>::MAX_QUEUE_SIZE) {
					
					boost::mutex::scoped_lock lock(queue_status_mutex);
					
					{
						boost::mutex::scoped_lock lock(io_mutex);
						std::cout << "Queue is full. Waiting..." << std::endl;
					}
					while(q.size() >= q.MAX_QUEUE_SIZE)
						queue_status.wait(lock);
				}
				else {

					for(int i = 0; i<std::numeric_limits<short>::max(); ++i) {
						T elem = boost::lexical_cast<T> ((double)rand() / (RAND_MAX + 1));
						{
							boost::mutex::scoped_lock lock(io_mutex);
							std::cout << "Producing: " << elem << std::endl;

					        //boost::xtime xt;
							//boost::xtime_get(&xt, boost::TIME_UTC);
							//xt.nsec += 3000;
							//boost::thread::sleep(xt);
						}
						q.add(elem);
					}

					// signal that element was just added to the queue
					queue_status.notify_all();
				}

			{
				boost::mutex::scoped_lock lock(is_done_mutex);
				is_done_flag = true;
			}

			// send out another notification as if there was another
			// element added to the queue; not true but all waiting consumers
			// are woken up and firts they'll check the flag if they should quit
			queue_status.notify_all();
		}
		catch( std::ios_base::failure ex )	{
			std::cout << ex.what();
		}
		catch( std::runtime_error re )	{
			std::cout << re.what();
		}
	}
};

template<typename T>
class consumer_type {

public:
	void operator()(thread_safe_queue<T>& q, 
		boost::condition& queue_status, 
		boost::mutex& queue_status_mutex,
		boost::mutex& is_done_mutex,
		bool& is_done_flag) {
		{
			boost::mutex::scoped_lock lock(io_mutex);
			std::cout << "Consumer thread is running..." << std::endl;
		}

		
		while(true) {

			boost::mutex::scoped_lock queue_status_lock(queue_status_mutex);	
			if(q.empty()) {
				{
					boost::mutex::scoped_lock lock(io_mutex);
					std::cout << "Queue is empty. Waiting..." << std::endl;
				}
				while(q.empty())
					queue_status.wait(queue_status_lock);
			}

			while(!q.empty()) {
				T elem = q.get();

				{
					boost::mutex::scoped_lock lock(io_mutex);
					std::cout << "Consuming : " << elem << std::endl;
				}

				///tokenize(s);

				//std::vector<std::string>::const_iterator citer;
				//{	
				//	boost::mutex::scoped_lock lock(io_mutex);
				//	for(citer = tokens_.begin(); citer != tokens_.end(); ++citer) {
				//		std::cout << *citer << " | ";
				//	}
				//	std::cout << std::endl;
				//}

				// done with token processing, now erase them!
//				tokens_.erase(tokens_.begin(), tokens_.end());
				// send out a notification that at least one element from the queue was processed
				queue_status.notify_one();
			}

			{
				boost::mutex::scoped_lock lock(is_done_mutex);
				if(is_done_flag == true)
					break;
			}
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
	thread_safe_queue<T> q_;
	
	// add a flag and a mutex for sync,
	// flagging when the producer is done; each consumer thread
	// should quit after the queue is empty
	// 
	boost::mutex is_done_mutex_;
	bool is_done_flag_;

	//
	boost::condition queue_status_;
	boost::mutex queue_status_mutex_;

	producer_type<T> producer_object_;
	consumer_type<T> consumer_object_;

	boost::thread producer_thread_;
	boost::thread consumer_thread_;
	boost::thread_group consumer_thread_group_;

public:
	manager() : is_done_flag_(false) {
		producer_thread_ = boost::thread(producer_object_, 
			boost::ref<thread_safe_queue<T> >(q_),
			boost::ref<boost::condition>(queue_status_),
			boost::ref<boost::mutex>(queue_status_mutex_),
			boost::ref<boost::mutex>(is_done_mutex_),
			boost::ref<bool>(is_done_flag_)
			);
		consumer_thread_ = boost::thread(consumer_object_, 
			boost::ref<thread_safe_queue<T> >(q_),
			boost::ref<boost::condition>(queue_status_),
			boost::ref<boost::mutex>(queue_status_mutex_),
			boost::ref<boost::mutex>(is_done_mutex_),
			boost::ref<bool>(is_done_flag_)
			);
		    
		for (int i = 0; i < 10; ++i)
			consumer_thread_group_.add_thread(
				new boost::thread(consumer_object_, 
				boost::ref<thread_safe_queue<T> >(q_),
				boost::ref<boost::condition>(queue_status_),
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
