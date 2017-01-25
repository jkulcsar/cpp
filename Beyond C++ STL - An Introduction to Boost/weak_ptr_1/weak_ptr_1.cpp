
//
// weak_ptr is an observer of a shared_ptr
// it does not interfere with the ownership of what a shared_ptr shares
//

#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include <iostream>
#include <cassert>

class A {};

int main(int argc, char** argv) {
	boost::weak_ptr<A> w;
	assert(w.expired());
	{
		boost::shared_ptr<A> p(new A());
		assert(p.use_count() == 1);
		w = p;
		assert(p.use_count() == w.use_count());
		assert(p.use_count() == 1);

		// create a shared_ptr from the weak_ptr
		boost::shared_ptr<A> p2(w);
		assert(p2==p);
	}
	assert(w.expired());
	boost::shared_ptr<A> p3 = w.lock();
	assert(!p3);

	return 0;
}