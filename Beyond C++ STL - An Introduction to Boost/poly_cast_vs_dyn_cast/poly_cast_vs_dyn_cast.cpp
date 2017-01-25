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
//
// When to use polymorphic_cast and dynamic_cast:
//
// (1) When a polymorphic cast failure is expected, use dynamic_cast<T*>. 
// It makes clear that the failure is not an error.
//
// (2) When a polymorphic cast must succeed in order for the logic 
// to be correct, use polymorphic_cast<T*>. It makes clear that a conversion 
// failure is an error.
//
// (3) When performing polymorphic casts to reference types, use dynamic_cast.
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

//
//
void polymorphic_cast_example(Base1* p) {
	Derived* pD = boost::polymorphic_cast<Derived*>(p);
	pD->print();

	Base2* pB = boost::polymorphic_cast<Base2*>(p);
	pB->only_base2();
}

void dynamic_cast_example(Base1* p) {
	Derived* pD = dynamic_cast<Derived*>(p);

	// the biggest disadvantage in using dynamic_cast instead of
	// polymorphic_cast is that we have to manually check the value
	// of the pointer to see if the cast succeeded and if not, throw
	// an exception
	if(!pD)
		throw std::bad_cast();
	pD->print();

	Base2* pB = dynamic_cast<Base2*>(p);
	if(!pB)
		throw std::bad_cast();
	pB->only_base2();
}

int main(int argc, char** argv) {

	Base1* p = new Derived;

	try {
		polymorphic_cast_example(p);
		dynamic_cast_example(p);
	}
	catch(std::bad_cast& e) {
		std::cout << e.what() << std::endl;
	}

	// please use smart pointers...
	delete p;

	return 0;
}