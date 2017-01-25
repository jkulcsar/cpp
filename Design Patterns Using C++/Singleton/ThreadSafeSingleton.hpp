
#ifndef THREADSAFESINGLETON_HPP_
#define THREADSAFESINGLETON_HPP_

#include "boost/thread/thread.hpp"
#include "boost/thread/mutex.hpp"
#include "boost/thread/condition.hpp"

#include "boost/shared_ptr.hpp"


class ThreadSafeSingleton {
	typedef boost::mutex::scoped_lock scoped_lock;
	static boost::mutex mutex_;

	static boost::shared_ptr<ThreadSafeSingleton> pInstance_;
protected:
	ThreadSafeSingleton() {}
public:

	// The creation of the Singleton has to be synchronized to make sure that only one Singleton 
	// can ever be created in a multithreaded environment. We would also like to acquire the 
	// needed lock for this synchronization only when the Singleton has not been created yet.

	// It is easy to make sure we won’t acquire the lock when it is not needed by checking 
	// whether our Singleton exists already or not; only when the pointer is 0 will we acquire 
	// the lock before we create the Singleton. It is still possible for a thread to be 
	// suspended immediately after the first check but before it receives the lock. 
	// Another thread might come in to get the lock and create the Singleton. 
	// When the lock is released, the first thread can acquire it and again it has to verify 
	// that the Singleton has not been created yet. This is the Double Checked Locking Pattern 
	// as conceived by Douglas Schmidt and Tim Harrison
	//
	static boost::shared_ptr<ThreadSafeSingleton> Instance() {
		if(!pInstance_) {
			scoped_lock lock(mutex_);
			if(!pInstance_)
				pInstance_ = boost::shared_ptr<ThreadSafeSingleton>(new ThreadSafeSingleton());
		}

		return pInstance_;
	}

	~ThreadSafeSingleton() {
	}
};

//boost::shared_ptr<ThreadSafeSingleton> ThreadSafeSingleton::pInstance_ = boost::shared_ptr<ThreadSafeSingleton>(new ThreadSafeSingleton());
boost::shared_ptr<ThreadSafeSingleton> ThreadSafeSingleton::pInstance_ = boost::shared_ptr<ThreadSafeSingleton>();
boost::mutex ThreadSafeSingleton::mutex_ = boost::mutex();

#endif