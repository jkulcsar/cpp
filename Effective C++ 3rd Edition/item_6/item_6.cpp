

//
// item 6:
// explicitly disallow the use of compiler-generated functions
// you do not want

#include <iostream>

#include "HomeForSale.hpp"


int main(int argc, char** argv) {

	HomeForSale home1; // 
//	HomeForSale home2(home1); // error: can't copy! (see below)

	HomeForSale2 another_home1;

//	HomeForSale2 another_home2 = another_home1; // this is an error
	
	// this is also a logical error, a house cannot just be copied 
	// into another house (since each is unique!) so logical errors 
	// can be avoided by enforcing better  default behavior 
	// of the type of objects

	return 0;
}