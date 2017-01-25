
#include <string>
#include "Widget.hpp"

//
// a simple function to call when memory allocation
// for a type of class (here: Widget) fails
// this function will be installed as the new-handler
void outOfMem() {};

int main(int argc, char** argv)
{
	//
	// install custom new-handler
	Widget::set_new_handler(outOfMem);
	//
	// if previous memory allocation fails, outOfMem() will be called
	Widget *pw1 = new Widget;

	//
	// if this mem. alloc. fails, the global new-handling function
	// will be called (if there is one!)
	std::string *ps = new std::string;

	//
	// set the Widget specific new-handler to null
	Widget::set_new_handler(0);
	//
	// if this memory allocation fails, an exception will be thrown!
	Widget *pw2 = new Widget;

	//
	// use nothrow version
	// we haven't defined the nothrow version for Widget, so just use the standard
	Widget* pw3 = ::new (std::nothrow) Widget;
	if(pw3 == 0)
	{
		//... testing pointer is only way to find out
		// if memory allocation failed;
		// this test may succeed
	}

	EnhancedWidget *pew1 = new EnhancedWidget;

	//
	// do some cleanup...
	if(pw1)
		delete pw1;
	if(pw2)
		delete pw2;
	if(pew1)
		delete pew1;
	if(ps)
		delete ps;

	return 0;
}
