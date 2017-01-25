#pragma once

//
// exception provide a solution to the problem of how to report problems
// from a constructor, since constructors do not return a separate value
// for the caller to test;
//
// exception handling allows the information that a construction failed
// to be transmitted out of the constructor
//

class MyVector
{
public:
	class Size {};
	enum { max = 32000 };

	MyVector(int sz) {
		if(sz < 0 || max < sz)
			throw Size();
	}

	virtual ~MyVector(void) {};
};
