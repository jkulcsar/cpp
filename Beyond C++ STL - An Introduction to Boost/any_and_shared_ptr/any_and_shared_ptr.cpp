
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "boost/any.hpp"
#include "boost/shared_ptr.hpp"

class A {
public:
	virtual ~A() {
		std::cout << "A::~A()\n";
	}

	void not_virtual() {
		std::cout << "A::not_virtual()\n";
	}

	virtual void is_virtual () {
		std::cout << "A:: is_virtual ()\n";
	}
};

class B : public A {
public:

	void not_virtual() {
		std::cout << "B::not_virtual()\n";
	}

	virtual void is_virtual () {
		std::cout << "B:: is_virtual ()\n";
	}
};

void examine(boost::any& a) {
	// try for boost::shared_ptr<A>
	try {
		boost::shared_ptr<A> ptr = boost::any_cast<boost::shared_ptr<A> >(a);
		std::cout << "This contained a boost::shared_ptr<A>" << std::endl;

		ptr->is_virtual();
		ptr->not_virtual();
		return;
	}
	catch(boost::bad_any_cast& ) {
	}

	// try for boost::shared_ptr<B>
	try {
		boost::shared_ptr<B> ptr = boost::any_cast<boost::shared_ptr<B> >(a);
		std::cout << "This contained a boost::shared_ptr<B>" << std::endl;

		ptr->is_virtual();
		ptr->not_virtual();
		return;
	}
	catch(boost::bad_any_cast& ) {
	}

	// If anything else (like just a string), ignore it
	std::cout << "The any didn't contain anything that concerns this function!"
		<< std::endl;
}

int main(int argc, char** argv) {
	std::cout << "Example of boost::any and boost::shared_ptr." << std::endl;

	boost::any a1(boost::shared_ptr<A>(new A));
	boost::any a2(std::string("just a string"));
	{
		// Things get really interesting: the third element contains a shared_ptr<A>
		// that is pointing to an instance of B. This is an example of how 
		// polymorphism works just the same for any as for other types. Of course, 
		// if we were using raw pointers, we could have used static_cast to store 
		// the pointer as the type that we want to be the identification tag that 
		// unlocks the any. Note that the function A::not_virtual is called 
		// instead of B::not_virtual. The reason is that the static type of the 
		// pointer is A*, not B*.
		boost::any b1(boost::shared_ptr<A>(new B));

		boost::any b2(boost::shared_ptr<B>(new B));

		// define a container of any objects
		std::vector<boost::any> vec;

		vec.push_back(a1);
		vec.push_back(a2);
		vec.push_back(b1);
		vec.push_back(b2);

		// let's examine each element in container
		std::for_each(
			vec.begin(),
			vec.end(),
			examine );

		std::cout << std::endl;
	}

	return 0;
}
