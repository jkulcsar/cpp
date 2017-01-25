
#include <iostream>
#include <typeinfo>

void foo()
{
	std::cout << "foo() called" << std::endl;
}

// define a function type
// here: FooT has the same type as foo()
typedef void FooT();

int main( int argc, char** argv)
{
	foo();	// direct call

	// print type of foo() and FooT
	std::cout << "Types of foo: " << typeid(foo).name() << std::endl;
	std::cout << "Types of FooT: " << typeid(FooT).name() << std::endl;

	// pointer-to-function
	FooT* pf = foo;		// implicit conversion (decay)
	pf();				// indirect call through function to pointer
	(*pf)();			// equivalent to pf()

	// print type of pointer-to-function
	std::cout << "Types of pf: " << typeid(pf).name() << std::endl;

	// reference-to-function
	FooT& rf = foo;		// no implicit conversion
	rf();

	// print type of the reference-to-function
	std::cout << "Types of rf: " << typeid(rf).name() << std::endl;

}