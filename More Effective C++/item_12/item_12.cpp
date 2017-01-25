
//
// Item 12: Understand how throwing an exception differs from
// passing a parameter or calling a virtual function
//
// There are thus three primary ways in which passing an object to a function 
// or using that object to invoke a virtual function differs from throwing 
// the object as an exception:
//
// (1) Exception objects are always copied; when caught by value, 
// they are copied twice. Objects passed to function parameters need not be copied at all. 
//
// (2) Objects thrown as exceptions are subject to fewer forms of type conversion 
// than are objects passed to functions. 
//
// (3) Catch clauses are examined in the order in which they appear in the source code,
// and the first one that can succeed is selected for execution. When an object is used 
// to invoke a virtual function, the function selected is the one that provides the best
// match for the type of the object, even if it's not the first one listed in the source code. 
//
//
// In general, you'll want to use the 
// throw;
// syntax to rethrow the current exception, because there's no chance that that will 
// change the type of the exception being propagated. Furthermore, it's more efficient, 
// because there's no need to generate a new exception object. 
//


#include <iostream>

class Widget {
};

class SpecialWidget : public Widget {
};

void passAndThrowWidget()
{
	SpecialWidget localSpecialWidget;
	//  ...
	Widget& rw = localSpecialWidget;    // rw refers to a SpecialWidget


	try {
		// ... do something here
		throw rw;                           // this throws an exception of type
											// Widget! (the static type of rw is Widget)
	}
	catch (SpecialWidget& w)	// catch SpecialWidget exceptions
	{
		//... handle the exception
			throw;			// rethrow the exception so it
	                        // continues to propagate
							// type of exception will be exactly as it was thrown,
							// even if type is derived (here: SpecialWidget)
    }
	catch (Widget& w)		// catch Widget exceptions
	{
		//... handle the exception
			throw w;		// propagate a copy of the
							// caught exception
	}
}



int main(int argc, char** argv) {

	passAndThrowWidget();
	return 0;
}