#pragma once

#include "GenericStack.hpp"

class IntStack_v1 {
public:
	IntStack_v1() {}
	virtual ~IntStack_v1() {}
	
	// here: the member functions are (implictly) inline
	// which means the cost of calling them is zero
	//
	void push(int *intPtr) {s.push(intPtr); }
	
	int* pop() { 
		return static_cast<int*>(s.pop());
	}
	
	bool empty() const {
		return s.empty();
	}

private:
	GenericStack_v1 s;

};

class IntStack : private GenericStack {
public:
	void push(int* intPtr) { GenericStack::push(intPtr); }
	int* pop() { return static_cast<int *>(GenericStack::pop()); }
	bool empty() { return GenericStack::empty(); }
};