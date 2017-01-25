
#include "boost/shared_ptr.hpp"
#include <vector>
#include <iostream>


// The two classes, A and B, contain a single virtual member function sing. 
// B derives publicly from A, and as you can see, the factory function createA 
// returns a dynamically allocated instance of B wrapped in a shared_ptr<A>. 
// In main, a std::vector containing shared_ptr<A> is filled with 10 elements, 
// and finally sing is invoked on each element. Had we been using raw pointers 
// as elements, the objects would need to be manually deleted. 
// In the example, this deletion is automatic, because the reference count of 
// each shared_ptr in the container is 1 as long as the vector is kept alive; 
// when the vector is destroyed, the reference counters all go down to zero, 
// and the objects are deleted. 
// It is interesting to note that even if the destructor of A had not been 
// declared virtual, shared_ptr would have correctly invoked the destructor of B! 
//

class A {
public:
	virtual void sing() = 0;
protected:
	virtual ~A() {}
};

class B : public A {
public:
	virtual void sing() {
		std::cout << "do re mi fa so la" << std::endl;
	}
};

boost::shared_ptr<A> createA() {
	boost::shared_ptr<A> p(new B());
	return p;
}




int main(int argc, char** argv) {

	typedef std::vector<boost::shared_ptr<A> > container_type;
	typedef container_type::iterator iterator;

	container_type container;

	for(int i=0; i<10; ++i) {
		container.push_back(createA());
	}

	std::cout << "The choir is gathered:" << std::endl;
	iterator end = container.end();
	for(iterator it = container.begin(); it != end; ++it) {
		(*it)->sing();
	}

	return 0;
}