
//
// item 14: Use reserve() to avoid unnecessary re-allocations.

#include <iostream>
#include <vector>

#include "..\ESTLUtil_rewrite.hpp"
#include "..\Widget.h"


int main(int argc, char** argv) {
	//
	// as elements are added to the vector,
	// several pre-allocations will occur
	{
		std::vector<int> v;
		for(int i = 0; i < 1000; ++i)
			v.push_back(i);
	}

	//
	// if we know the exact number of elements
	// (or at least close enough), pre-allocate it!
	{
		std::vector<int> v;
		v.reserve(1000);
		for(int i = 0; i < 1000; ++i)
			v.push_back(i);
		printContainer(v);
	}


	//
	// same applies to strings
	{
		std::string s;
		s = "This is a test";

		// add another character only if there's already
		// capacity for it
		if(s.size() < s.capacity())
			s.push_back('X');

		printContainer(s);
	}

	return 0;
}
