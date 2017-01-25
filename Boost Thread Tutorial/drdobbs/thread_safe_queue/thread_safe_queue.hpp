
#include "boost/thread/thread.hpp"
#include "boost/thread/mutex.hpp"
#include "boost/thread/condition.hpp"

#include <queue>

template<typename T>
class thread_safe_queue {

	typedef boost::mutex::scoped_lock scoped_lock;

	boost::mutex mutex_;
	std::queue<T> q_;
public:
	static const std::queue<std::string>::size_type MAX_QUEUE_SIZE = 200;
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
};
