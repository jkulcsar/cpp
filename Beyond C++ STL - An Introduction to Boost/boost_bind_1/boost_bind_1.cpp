
#include <iostream>
#include <algorithm>
#include <cassert>

#include <boost/bind.hpp>

class A {
	int _value;
public:
	int getValue() const {
		return _value;
	}
	A(int& i) : _value(i) {}
	~A() {}
};

int f(int a, int b) {
	return a + b;
}

int g(int a, int b, int c) {
	return a + b + c;
}

int h(A& a, int b) {
	return a.getValue() + b;
}

//
// using boost::bind with function operators
struct F {
	int operator()(int a, int b) {
		return a - b;
	}
	bool operator()(long a, long b) {
		return a == b;
	}
};

//
// By default, bind makes a copy of the provided function object. boost::ref 
// and boost::cref can be used to make it store a reference to the function
// object, rather than a copy. This can be useful when the function object is
// noncopyable, expensive to copy, or contains state; of course, in this case
// the programmer is expected to ensure that the function object is
// not destroyed while it's still being used.
//
// When the function object exposes a nested type named result_type, 
// the explicit return type can be omitted
//
struct F2 {
	int s_;
	typedef void result_type;
	void operator()(int x) {
		s_ += x;
	}
};

int main(int argc, char** argv) {
	int result = 0;
	
	result = boost::bind<int>(f, 1, 2)();
	std::cout << result << std::endl;

	int x = 5;
	result = boost::bind<int>(g, _1, 6, 6)(x);
	std::cout << result << std::endl;

	A a(x);
	result = boost::bind<int>(h, _1, 6)(a);
	std::cout << result << std::endl;

	x = 104;
	F fctor;	// functor
	result  = boost::bind<int>(fctor, _1, _1)(x);
	std::cout << result << std::endl;
	std::cout << boost::bind<long>(fctor, _1, _1)(x) << std::endl;

// When the function object exposes a nested type named result_type, 
// the explicit return type can be omitted
//
	F2 fctor2 = { 0 };
	int simple_array[] = {1, 2, 3};
	std::for_each( simple_array, simple_array + 3, boost::bind( boost::ref(fctor2), _1 ) );
	assert( fctor2.s_ == 6);

	return 0;
}
