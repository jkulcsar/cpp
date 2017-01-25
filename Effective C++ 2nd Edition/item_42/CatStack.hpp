#pragma once

#include "GenericStack.hpp"

class Cat {};

class CatStack_v1 {
public:
	CatStack_v1() {}
	virtual ~CatStack_v1() {}

	// here: member functions are (implictly) inline
	// so the cost of calling them is zero
	//
	void push(Cat* catPtr) {
		s.push(catPtr);
	}

	Cat* pop() {
		return static_cast<Cat*>(s.pop());
	}

	bool empty() {
		return s.empty();
	}

private:
	GenericStack_v1 s;		// implementation
};

class CatStack : private GenericStack {
public:
	void push(Cat* catPtr) { GenericStack::push(catPtr); }
	Cat* pop() { return static_cast<Cat *>(GenericStack::pop()); }
	bool empty() { return GenericStack::empty(); }
};