
#include <iostream>

#include "Singleton.hpp"
#include "ThreadSafeSingleton.hpp"

boost::mutex io_mutex;

class SingletonUser {
	unsigned int id_;

	void acquire_use_singleton() {
		for( unsigned int i = 0; i < 200; ++i) {
			boost::shared_ptr<ThreadSafeSingleton> pTSS = ThreadSafeSingleton::Instance();
			{
				boost::mutex::scoped_lock lock(io_mutex);
				std::cout << "ID: " << id_  << " acquired instance: " << std::ios_base::hex << pTSS << std::endl;
			}
		}
	}
public:
	SingletonUser(const unsigned int id) : id_(id) {
	}

	void operator()() {
		acquire_use_singleton();
	}
};


int main(int argc, char** argv) {

	Singleton* pSingleton1 = Singleton::Instance();
	Singleton* pSingleton2 = Singleton::Instance();

	SingletonUser su1(1), su2(2);

	boost::thread thread_1 = boost::thread(su1);
	boost::thread thread_2 = boost::thread(su2);


	thread_1.join();
	thread_2.join();

	return 0;
}