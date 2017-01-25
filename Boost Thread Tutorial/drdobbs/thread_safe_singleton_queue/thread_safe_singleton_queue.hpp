
#ifndef THREADSAFESINGLETONQUEUE_HPP_
#define THREADSAFESINGLETONQUEUE_HPP_

#include "thread_safe_queue.hpp"

#include "boost/thread/thread.hpp"
#include "boost/thread/mutex.hpp"
#include "boost/thread/condition.hpp"

#include "boost/shared_ptr.hpp"

#include <iostream>

extern boost::mutex io_mutex;


//
// wrap the ThreadSafeQueue into a ThreadSafeSingleton
// this will ensure a unique instance accross the application
// the ThreadSafeSingleton, as the name suggests, synchronizes concurrent access 
// to the one ThreadSafeQueue instance, using the Double-Check Locking Pattern
//

template<typename T>
class ThreadSafeSingleton {
	typedef boost::mutex::scoped_lock scoped_lock;
	static boost::mutex mutex_;

	static boost::shared_ptr<ThreadSafeQueue<T> > pQueueInstance_;
protected:
	ThreadSafeSingleton() {}
public:

	// The creation of the Singleton has to be synchronized to make sure that only one Singleton 
	// can ever be created in a multithreaded environment.
	// the lock for this synchronization needs to be acquired only when the Singleton 
	// has not been created yet.
	// Using the Double Checked Locking Pattern (DCLP)

	static boost::shared_ptr<ThreadSafeQueue<T> > GetQueueInstance() {
		if(!pQueueInstance_) {
			{
				boost::mutex::scoped_lock lock(io_mutex);
				std::cout << "Acquiring singleton queue..." << std::endl;
			}

			scoped_lock lock(mutex_);
			if(!pQueueInstance_) {
				{
					boost::mutex::scoped_lock lock(io_mutex);
					std::cout << "Creating singleton queue..." << std::endl;
				}

				pQueueInstance_ = boost::shared_ptr<ThreadSafeQueue<T> >(new ThreadSafeQueue<T>());
			}
		}

		return pQueueInstance_;
	}

	~ThreadSafeSingleton() {
	}
};
template<typename T>
boost::shared_ptr<ThreadSafeQueue<T> > ThreadSafeSingleton<T>::pQueueInstance_ = boost::shared_ptr<ThreadSafeQueue<T> >();

template<typename T>
boost::mutex ThreadSafeSingleton<T>::mutex_;

#endif