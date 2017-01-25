
#include <memory>
#include "NewHandlerSupport.hpp"
#include "NewHandlerHolder.hpp"

template<typename T>
std::new_handler NewHandlerSupport<T>::set_new_handler(std::new_handler p) throw()
{
	std::new_handler oldHandler = _currentHandler;
	_currentHandler = p;
	return oldHandler;
}

template<typename T>
void* NewHandlerSupport<T>::operator new(std::size_t size) throw(std::bad_alloc)
{
	// install the new-handler for this class
	NewHandlerHolder h(std::set_new_handler(_currentHandler));
	
	return ::operator new(size);

	// on exit, destructor of NewHandlerHolder will restore the old(global) new-handler
}

//
template<typename T>
std::new_handler NewHandlerSupport<T>::_currentHandler = 0;