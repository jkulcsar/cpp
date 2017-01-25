
//
// definition: explicit keyword can only be applied to in-class constructors;
// an explicit constructor can not take part in implicit conversions;
// it can only be used to explictly construct an object
//
// Scott Meyers advice: constructors declared explicit are usually preferable
// instead of non-explicit, because they often prevent compilers from performing
// unexpected (and often unintended) type conversions;
// unless there's a good reason to allow a ctor to be used in implicit type
// conversions, declare it explicit
// Effective C++ (3rd edition) Item 24 uses/discusses this with class Rational
//
// Stroustrup book: by default, a single argument constructor also defines an
// implicit conversion; for example:
// complex z = 2; // initialize z with complex(2);
//
// The following example is from MSDN:

#include <iostream>

class C
{
public:
	int	i_;

	// an explicit copy constructor:
	explicit C(const C&)
	{
		std::cout << "in copy ctor of C" << std::endl;
	}

	// an explicit constructor
	explicit C(int i) : i_(i)
	{
		std::cout << "in ctor C(int)" << std::endl;
	}

	// default constructor
	C() : i_(0)
	{
		std::cout << "in default ctor C()" << std::endl;
	}
};

class C2
{
public:
	int i_;

	// an explicit constructor
	explicit C2(int i) : i_(i)
	{
		std::cout << "in ctor C2(int)" << std::endl;
	}
};


// Trying to copy a class whose copy constructor is explicit.
// Declaring a copy constructor with explicit prevents
// passing/returning objects of a class to/from functions.
//
//C f(C c)
//{
//	c.i_ = 2;
//	return c;	// call to copy constructor
//}

C& ff(C& c)
{
	c.i_ = 10;
	return c;
};

void f2(C2)
{
}

void g(int i)
{
	//	f2(i);
	f2(C2(i));
}

int main(int argc, char** argv)
{
	C c, d;
	d = ff(c);	// c is copied
	g(11);

	return 0;
}