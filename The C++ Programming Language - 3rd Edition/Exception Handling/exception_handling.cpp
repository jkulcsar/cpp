
#include <exception>

#include "MathErr.hpp"
#include "IntOverflow.hpp"
#include "FilePtr.hpp"
#include "MyVector.hpp"
#include "NetFileErr.hpp"

void g() {
	throw IntOverflow("+", 1, 1);
}

void another_g() {
	throw IntOverflow("+", 1, 1);
}

void f_slicing() {
	try {
		g();
	}
	catch(MathErr m) {
		//
		// when MathErr is entered, m is a MathErr object
		// so information will be lost even if the thrown
		// exception was a IntOverflow object ('slicing' occurs)
		//
		m.debug_print();
	}
}

int add(int x, int y) throw(MathErr, IntOverflow) {
	if( (x>0 && y>0 && x>INT_MAX-y) || (x<0 && y<0 && x<INT_MIN-y))
		throw IntOverflow("+", x, y);
	return x + y;
}

void f_no_slicing() {
	//
	// as always, pointers or references can be used to avoid
	// loosing information permanently (due to 'slicing')
	// 
	try {
		int i1 = add(1,2);
		int i2 = add(INT_MAX, -2);
		int i3 = add(INT_MAX, 2);	// will throw exception
	}
	catch(MathErr& m) {
		m.debug_print();
	}
}

//
// acquire and initialize model
// This is a general technique that relies on the properties of constructors and
// destructors and their interaction with exception handling.
//
// An object is not considered constructed until its constructor has completed.
// Then and only then will stack unwinding call the destructor for the object.
// An object composed of subobjects is constructed to the extent that its 
// subobjects have been constructed. 
//
// An array is constructed to the extent that its elements have been constructed (and only fully 
// constructed elements are destroyed during unwinding).
//
void use_file(const char* filename, const char* attributes) {
	FilePtr file(filename, attributes);
	// use file object here...
}


//
// Exceptions and Constructors
//
// exceptions provide a solution to the problem of how to report problems
// from a constructor, since constructors do not return a separate value
// for the caller to test;
//
// exception handling allows the information that a construction failed
// to be transmitted out of the constructor
//
void use_vector(int sz) {
	try {
		MyVector v(sz);
	}
	catch(MyVector::Size& ex) {
		std::cout << "MyVector::Size exception caught!" << std::endl;
	}
}


//
// Exceptions and Destructors
//
// From the point of view of exception handling, a dtor can be called
// in two ways:
// (1) normal call: normal exit from a scope or call to delete
// (2) call during exception handling: during stack unwinding, 
// the exception-handling mechanism exits a scope containing an object
// with a destructor.
class X {
public:
	~X();
};
X::~X() {
	// The standard library function u n c a u g h t _ e x c e p t i o n () 
	// returns t r u e if an exception has been thrown but hasn’t yet been caught.
	// This allows the programmer to specify different actions in a destructor
	// depending on whether an object is destroyed normally or as part of stack unwinding

	if(std::uncaught_exception()) {
		//
		// destructor is being called as part of another
		// exceptions stack unwinding
		// if we throw here, terminate() will be called so 
		// we better catch everything that might be locally thrown!
		try {
			g();	// might throw, see above
		}
		catch(...) {
			// do some extra logic here
			// must be in catch-all because if we don't catch locally thrown
			// exceptions while dtor is already being called as part of another exception
			// unwinding, terminate() will be called;
			// try it! uncomment the NetworkErr catch section and comment out this (...)
			// catch section!
			std::cout << "Dtor of X called as part of unwinding another exception... " << std::endl;
		}
		//catch(NetworkErr& ne) // NetworkErr will never be thrown in this context
		//{
		//	std::cout << "This will never be printed, terminate() is called... " << std::endl;
		//}
	}
	else
	{
		std::cout << "Dtor of X called normally... " << std::endl;
	}
}


void f_network_aware()
{
	bool can_handle_network_error_completely = true;
	try
	{
		// something that may throw a network error...
	}
	catch(NetworkErr& e)
	{
		if( can_handle_network_error_completely )
		{
			// call actual logic to handle this type
			// of exception:
			// my_network_error_handler(e);
			//
			// return 'normally' from this function
			return;
		}
		else
		{
			// do what we can do here
			//
			// re-throw the exception so the caller may be aware
			// of it and/or handle it
			throw; 
		}
	}
}

void f_not_network_aware()
{
	try
	{
		// something else
	}
	catch(FileSystemErr& e)
	{
		// ...
	}
}

//
// exception specifications
void f(int a) throw(MathErr, NetFileErr);

void f(int a) throw(MathErr, NetFileErr)
{
	try
	{
		// something
	}
	catch(MathErr& me)
	{
		throw; // re-throw original exception
	}
	catch(NetFileErr& nfe)
	{
		throw; // re-throw original exception
	}
	catch(...)
	{
		std::unexpected();
	}
}

int main(int argc, char** argv) {
	//
	// 'slicing' occurs:
	f_slicing();

	f_no_slicing();

	use_file("text.txt", "a+");

	use_vector(20000); // should be OK, no Size exception thrown
	use_vector(33000); // should throw/catch Size exception


	//
	// when using composite exceptions (through multiple inheritance)
	// is called non-hierarchical (not a tree structure) because
	// one exception belongs to two groups;
	// here: NetFileErr can be caught in functions that are network aware
	// but also by functions that are not even network aware, may be considering
	// such exceptions as filesystem errors:
	f_network_aware();
	f_not_network_aware();

	//
	try
	{
		f(10);
	}
	catch(MathErr& me)
	{
		me.debug_print();
	}

	//
	// simulate a call to the X destructor
	// another_g() will throw while the local scope object x
	// is still on the stack of this try {} block scope
	try
	{
		X x;
		another_g();
	}
	catch(MathErr& me)
	{
		std::cout << "This time the IntOverflow is caught... " << std::endl;
	}

	X x;

 	return 0;
}