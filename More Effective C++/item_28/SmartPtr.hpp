
#pragma once

#include <memory>
template<typename T>
class SmartPtr
{
public:
	// create a smart pointer to an object
	// given a dumb pointer to it
	// initialize pointer by default to 0 (null)
	SmartPtr(T* realPtr = 0);

	// copy a smart pointer
	SmartPtr(SmartPtr&);

	// assignement op
	SmartPtr& operator=(SmartPtr&);

	// dtor
	~SmartPtr();

	// de-reference a smart pointer
	// to get to a member it points to
	T* operator->() const;

	// de-reference a smart pointer
	T& operator*() const;

private:

	// the wrapped object pointer
	T* pointee;
};