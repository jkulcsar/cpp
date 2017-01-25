

#include "boost/thread/thread.hpp"
#include "boost/thread/mutex.hpp"
#include "boost/thread/condition.hpp"

#include <queue>


//
// ThreadSafeQueue is a very simple wrapper around an std::queue
// container, using a mutex for synchronizing concurrent access
// to the queue;
// it's public interface is based on and a simplified version of std::queue
//
template<typename T>
class ThreadSafeQueue {

	typedef boost::mutex::scoped_lock scoped_lock;

	boost::mutex mutex_;
	std::queue<T> q_;
public:
	static const typename std::queue<T>::size_type MAX_QUEUE_SIZE = 5;
	void add(T const& elem) {
		scoped_lock lock(mutex_);
		q_.push(elem);
	}

	T get() {
		scoped_lock lock(mutex_);
		T elem;
		if(!q_.empty()) {
			elem = q_.front();
			q_.pop();
		}
		
		return elem;
	}

	const bool empty() {
		scoped_lock lock(mutex_);
		return q_.empty();
	}

	const typename std::queue<T>::size_type size() {
		scoped_lock lock(mutex_);
		return q_.size();
	}
protected:
	// do not allow ThreadSafeQueue objects created on stack
	//~ThreadSafeQueue() {}
private:
	// this should disable also creating on the heap
	// in this case we need it since the queue is a shared_ptr
	// in the Singleton class;
	// creating a new queue on the heap is OK however can not call
	// delete on this pointer since dtor is protected
	//static void *operator new(size_t);
	//static void operator delete(void *);
};