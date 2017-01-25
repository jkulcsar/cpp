
//
// Item 29: Reference counting

#include "SimpleString.hpp"
#include "RCString.hpp"

#include "String.hpp"

#include "RCWidget.hpp"

int main(int argc, char** argv)
{
	//
	// each SimpleString has it's own copy of the actual data
	SimpleString ss1, ss2, ss3, ss4, ss5;
	ss1 = ss2 = ss3 = ss4 = ss5 = "This is SimpleString";

	RCString rc1("This is RCString with Reference Counting");
	RCString rc2(rc1);		// init rc2 from rc1
	RCString rc3("");		// empty string
	rc3 = rc2;				// copy rc2 into rc3; should only refcount!


	String s1, s2;
	s1 = s2 = "This is a real String!";
	// now call op[] to modify one of the strings
	// and watch how the sharing is broken off:
	s1[3] = 'a';

	//
	// example using a more generic solution,
	// a ref-counted wrapper around a class that 
	// can not be modified; use the ref-counted wrapper
	// objects as-a original type with the benefit of
	// being ref-counted:
	//
	RCWidget widgetA(1); // 'size' here is the size of a Widget array?
	RCWidget widgetB(2); // elaborate/correct based on the RC Array in
	widgetA = widgetB;   // the "Effective" project!
	// note: Widget doe not have op[] so perhaps is not an array?
	//
	// now use the ref-counted widgets:
	widgetA.doThis();
	int iRes = widgetB.showThat();

	return 0;
}