
#include "Widget.hpp"
#include "NewHandlerHolder.hpp"

//
// static class members must be defined outside the class definition
// here: initialize to null in class implementation file
std::new_handler Widget::_currentHandler = 0;


//
// set the NEW operator new handler
// return the pointer to the old operator new handler
//
// The set_new_handler function in class X will save 
// whatever pointer is passed to it. It will return 
// whatever pointer had been saved prior to the call.
// This is exactly what the standard version 
// of set_new_handler does: 
//
std::new_handler Widget::set_new_handler(std::new_handler p)
{
	std::new_handler oldHandler = _currentHandler;
	_currentHandler = p;
	return oldHandler;
}

void* Widget::operator new(std::size_t size) throw(std::bad_alloc)
{
	// install the new-handler for this class
	NewHandlerHolder h(std::set_new_handler(_currentHandler));

	return ::operator new(size);

	// on exit, destructor of NewHandlerHolder will restore the old(global) new-handler
}