
#include <iostream>
#include <string>

#include "X.hpp"

void noMoreMemory()
{
}




int main( int argc , char** argv )
{
	X::set_new_handler(noMoreMemory);
	X* pX1 = new X;

	//
	// if the previous memory allocation fails,
	// call the global new-handling function
	// (if there is one)
	std::string *ps = new string;

	X::set_new_handler(0);                     // set the X-specific
                                               // new-handling function
                                               // to nothing (i.e., null)

	X *pX2 = new X;                                // if memory allocation
                                               // fails, throw an exception
                                               // immediately. (There is
                                               // no new-handling function
                                               // for class X.)
	if( pX1 != 0 )
		delete pX1;
	if( pX2 != 0 )
		delete pX2;
	if( ps != 0 )
		delete ps;

	return 0;
}