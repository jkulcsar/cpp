#include "X.hpp"

//
// static class members must be defined outside of class declaration
//
new_handler X::currentHandler;      // sets currentHandler
                                    // to 0 (i.e., null) by
                                    // default

//
// The set_new_handler function in class X will save 
// whatever pointer is passed to it. It will return 
// whatever pointer had been saved prior to the call.
// This is exactly what the standard version 
// of set_new_handler does: 
//
new_handler X::set_new_handler(new_handler p)
{
  new_handler oldHandler = currentHandler;
  currentHandler = p;
  return oldHandler;
}

void * X::operator new(size_t size)
{
	//
	// install X's handler
	new_handler globalHandler = std::set_new_handler(currentHandler);

	void *memory;

	try {
		//
		// attempt allocation
		memory = ::operator new(size);
	}
	catch(std::bad_alloc&)
	{
		//
		// restore handler
		// propagate exception
		std::set_new_handler(globalHandler);
		throw;
	}

	//
	// restore handler
	std::set_new_handler(globalHandler);

	return memory;
}

X::X(void)
{
}

X::~X(void)
{
}
