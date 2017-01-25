
#include <iostream>
#include <string>
#include "boost/cast.hpp"


//
// Refresher on dynamic_cast:
// - when invoked on a reference, it may throw an exception if cast fails;
// - when invoked on a pointer, if cast fails, the returned pointer is null;
//
// Polymorphic_cast always throws an exception if cast fails.
//

class Base1 {
public:
	virtual void print() {
		std::cout << "Base1::print()" << std::endl;
	}
	virtual ~Base1() {}
};

class Base2 {
public:
	// non-virtual!
	void only_base2() {
		std::cout << "only_base2()" << std::endl;
	}

	virtual ~Base2() {}
};

class Derived : public Base1, public Base2 {
public:
	virtual void print() {
		std::cout << "Derived::print()" << std::endl;
	}
	void only_here() {
		std::cout << "Derived::only_here()\n";
	}

	// non-virtual!
	void only_base2() {
		std::cout << "Oops, here too!\n";
	}
};

int main(int argc, char** argv) {

	Base1* p1 = new Derived;

	p1->print();

	try {
		Derived* pD = boost::polymorphic_cast<Derived*>(p1);
		pD->only_here();
		pD->only_base2();

		//
		// to be able to call the non-virtual function Base2::only_base2()
		// we need to perform a crosscast; here 'p1' is of type Derived
		// and if the only_base2() function was virtual, Derived::only_base2()
		// would have been called
		Base2* pB = boost::polymorphic_cast<Base2*>(p1);
		pB->only_base2();

	}
	catch(std::bad_cast& e) {
		std::cout << e.what() << std::endl;
	}

	delete p1;

	return 0;
}