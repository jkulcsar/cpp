
#include "thread_safe_singleton_queue.hpp"

#include <boost/thread/thread.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>  
#include <boost/thread/xtime.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/limits.hpp>

#include <boost/ref.hpp>

#include <iostream>
#include <string>
#include <time.h>

//
// http://stackoverflow.com/questions/1410649/waiting-for-multiple-condition_variable-variables-in-boost
// http://stackoverflow.com/questions/2850091/wait-on-multiple-condition_variable-variables-on-linux-without-unnecessary-sleeps
// http://lists.boost.org/Archives/boost/2001/10/18407.php
//

				//
				//boost::condition_variable condvar;
				//boost::mutex mutex;
				//bool finished1 = false;
				//bool finished2 = false;

				//void longComputation1()
				//{
				//	{
				//		boost::lock_guard<boost::mutex> lock(mutex);
				//		finished1 = false;
				//	}
				//	// Perform long computation
				//	{
				//		boost::lock_guard<boost::mutex> lock(mutex);
				//		finished1 = true;
				//	}
				//	condvar.notify_one();
				//}

				//void longComputation2()
				//{
				//	{
				//		boost::lock_guard<boost::mutex> lock(mutex);
				//		finished2 = false;
				//	}
				//	// Perform long computation
				//	{
				//		boost::lock_guard<boost::mutex> lock(mutex);
				//		finished2 = true;
				//	}
				//	condvar.notify_one();
				//}

				//void somefunction()
				//{
				//	// Wait for long computations to finish without "spinning"
				//	boost::lock_guard<boost::mutex> lock(mutex);
				//	while(!finished1 && !finished2)
				//	{
				//		condvar.wait(lock);
				//	}

				//	// Computations are finished
				//}



boost::mutex io_mutex;

//
// using the Producer type we instantiate the callable objects called by the boost::thread instances
// here: acquire the singleton instance of the queue and try to add an element;
// if queue is full, block on queue_status condition_variable, signaled by Consumer types when a new element
// has been removed (and processed) from the queue
//

template<typename T>
class Producer {
public:

	Producer() {}
	
	void operator()( 
			boost::condition_variable& still_working_cond,
			boost::mutex& still_working_mutex,
			bool& production_done_flag,
			bool& data_queue_empty_flag
			) {
		{
			boost::lock_guard<boost::mutex> lock(io_mutex);
			std::cout << "Producer thread running..." << "\t" << boost::this_thread::get_id() << std::endl;
		}

		boost::shared_ptr<ThreadSafeQueue<T> > q = ThreadSafeSingleton<T>::GetQueueInstance();

		try
		{
			{
				boost::lock_guard<boost::mutex> lock(still_working_mutex);
				production_done_flag = false;
				data_queue_empty_flag = true;
			}

			for(int i = 0; i<13000/*std::numeric_limits<short>::max()*/; ++i) {
				if(q->size() >= q->MAX_QUEUE_SIZE) {
						
						boost::unique_lock<boost::mutex> lock(still_working_mutex);
						
						{
							boost::lock_guard<boost::mutex> lk(io_mutex);
							std::cout << "Queue is full. Waiting..." << "\t" << boost::this_thread::get_id() << std::endl;
						}

						while(q->size() >= q->MAX_QUEUE_SIZE)
							still_working_cond.wait(lock);
					}
					else {

							T elem = boost::lexical_cast<T> ((double)rand() / (RAND_MAX + 1));
							{
								boost::lock_guard<boost::mutex> lk(io_mutex);
								std::cout << "Producing: " << elem << std::endl;
							}
							q->add(elem);

							data_queue_empty_flag = false;
							// signal that element was just added to the queue
							still_working_cond.notify_all();
					}
			}

	
			//
			// producer is done
			{
				boost::lock_guard<boost::mutex> lock(still_working_mutex);
				production_done_flag = true;
			}

			// send out another notification
			// all waiting consumers are woken up 
			// and check the flag if they should quit
			still_working_cond.notify_all();
		}
		catch( std::ios_base::failure ex )	{
			std::cout << ex.what();
		}
		catch( std::runtime_error re )	{
			std::cout << re.what();
		}
	}
};

//
// using the Consumer type we instantiate the callable objects called by the boost::thread instances
// here: acquire the singleton instance of the queue and try to remove an element;
// if queue empty, block on queue_status condition_variable, signaled by Producer types when a new element
// has been added to the queue
//
template<typename T>
class Consumer {

public:
	void operator()(
			boost::condition_variable& still_working_cond,
			boost::mutex& still_working_mutex,
			bool& production_done_flag,
			bool& data_queue_empty_flag
			) {

		{
			boost::lock_guard<boost::mutex> lock(io_mutex);
			std::cout << "Consumer thread is running..." << "\t" << boost::this_thread::get_id() << std::endl;
		}
		
		// Wait, without "spinning"
		boost::unique_lock<boost::mutex> lock(still_working_mutex);
		while(!production_done_flag || !data_queue_empty_flag)
		{
			{
				boost::lock_guard<boost::mutex> lk(io_mutex);
				std::cout << "Consumer status: prod_done " << production_done_flag << " queue_empty " << data_queue_empty_flag << "\t" << boost::this_thread::get_id() << std::endl;
			}
			still_working_cond.wait(lock);

			boost::shared_ptr<ThreadSafeQueue<T> > q = ThreadSafeSingleton<T>::GetQueueInstance();

			{
//					while(!q->empty() )
					if(!q->empty() )
					{
						T elem = q->get();
						{
							boost::lock_guard<boost::mutex> lock(io_mutex);
							std::cout << "Consuming : " << "\t" << elem << "\t" << boost::this_thread::get_id() << std::endl;
						}

						// got a local copy of the element so,
						// send out a notification that at least one element from the queue was processed
						// so producer can add at least another one
						still_working_cond.notify_one();

						//// do some more elaborate processing of the element just read from the queue
						//boost::xtime xt;
						//boost::xtime_get(&xt, boost::TIME_UTC);
						//xt.nsec += 10;
						//boost::thread::sleep(xt);
					}
					else
//						if(q->empty())
						{
							{
								boost::lock_guard<boost::mutex> lock(io_mutex);
								std::cout << "Queue is empty." << "\t" << boost::this_thread::get_id() << std::endl;
							}

							//
							// set flag that queue is empty!
							// so producer is woken up 
							data_queue_empty_flag = true;
							still_working_cond.notify_all();
						}
//				}
			}
		}

		{
			boost::lock_guard<boost::mutex> lock(io_mutex);
			std::cout << "Consumer thread " << boost::this_thread::get_id() << " quit!" << std::endl;
		}
	}
};

//
// the Manager class maintains the thread objects, both producer and consumers
// as well as the sync objects on the status of the queue;
// the threads can block on the condition_variable of the queue: producers will block if
// the size of the queue reaches max and consumers can block on the condition_variable if
// the queue is empty
template<typename T>
class Manager {

	//
	// usually, a central class that manages the overall data flow would
	// hold a unique instance of the data structure; here: the queue
	// since the queue is now wrapped into a thread-safe singleton,
	// each thread can access it directly, no need for the Manager
	// to pass it in as parameter to the thread ctors

	// shared queue of type T elements
	//ThreadSafeQueue<T> q_;
	
	// add a flag and a mutex for sync,
	// flagging when the producer is done; each consumer thread
	// should quit after the queue is empty
	// 
	boost::condition_variable still_working_cond_;
	boost::mutex still_working_mutex_;
	bool production_done_flag_;
	bool data_queue_empty_flag_;


	Producer<T> producer_object_;
	Consumer<T> consumer_object_;

	boost::thread producer_thread_;
	boost::thread consumer_thread_;
	boost::thread_group consumer_thread_group_;

public:
	// start by this initial assumptions:
	// production is not done (is just about to start)
	// and data queue is/must be empty at this point
	Manager() : production_done_flag_(false), data_queue_empty_flag_(true) {

		//
		// create a Producer thread
		producer_thread_ = boost::thread(producer_object_, 
			boost::ref<boost::condition_variable>(still_working_cond_),
			boost::ref<boost::mutex>(still_working_mutex_),
			boost::ref<bool>(production_done_flag_),
			boost::ref<bool>(data_queue_empty_flag_)
			);
		//
		// create a Consumer thread
		//consumer_thread_ = boost::thread(consumer_object_, 
		//	boost::ref<boost::condition_variable>(queue_status_),
		//	boost::ref<boost::mutex>(queue_status_mutex_),
		//	boost::ref<boost::mutex>(is_done_mutex_),
		//	boost::ref<bool>(is_done_flag_)
		//	);
		    
		//
		// create a thread_group of Consumer threads
		// create new callable Consumer objects for each new thread

		for (int i = 0; i < 7; ++i)
			consumer_thread_group_.add_thread(
			new boost::thread( *boost::shared_ptr<Consumer<T> >(new Consumer<T>()), 
				boost::ref<boost::condition_variable>(still_working_cond_),
				boost::ref<boost::mutex>(still_working_mutex_),
				boost::ref<bool>(production_done_flag_),
				boost::ref<bool>(data_queue_empty_flag_)
				));



		//
		// join all of the threads created above
		producer_thread_.join();
//		consumer_thread_.join();
		consumer_thread_group_.join_all();
	}
};



int main(int argc, char** argv) {
	
	// seed the random number generator
	srand( (unsigned)time( NULL ) );

	// create a Manager object, passing in the type of the queue elements;
	Manager<std::string> manager_object;

	return 0;
}
