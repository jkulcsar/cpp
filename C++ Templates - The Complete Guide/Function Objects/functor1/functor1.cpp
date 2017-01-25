
#include <iostream>
//#include <>

//
// functors: objects of a class with overloaded function call operator
//
// most important feature of functors over pointers-to-function:
// the ability to associate some state (data) with the function
//
// class for function objects that return a constant value
class ConstantIntFunctor
{
private:
	int value;
public:
	// ctor: initialize (constant) value to return
	ConstantIntFunctor(int c) : value(c) {
	}

	// overloaded function call operator
	int operator() () const {
		return value;
	}
};

//
// client function that uses the function object
void client(ConstantIntFunctor const& cif)
{
	std::cout << "calling back functor yields: " << cif() << std::endl;
}

int main(int argc, char** argv)
{
	ConstantIntFunctor seven(7);
	ConstantIntFunctor fourty_two(42);

	// direct call of functor's operator(), not a function call!
	std::cout << "direct call to functor yields: " << seven() << std::endl;

	// make two calls through a simple function, passing functor objects
	// as references
	client(seven);
	client(fourty_two);

	return 0;
}