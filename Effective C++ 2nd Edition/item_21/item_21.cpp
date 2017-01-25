#include <vector>


int main(int argc, char** argv[])
{
	char greeting[] = "Hello";

	//
	// if the word const appears to the left of the asterisk,
	// what's pointed to is constant;
	// if the word const appears to the right of the asterisk,
	// the pointer itself is constant;
	// if const appears on both sides, both are constant.
	//
	char *p1 = greeting;                    // non-const pointer,
                                            // non-const data

	const char *p2 = greeting;              // non-const pointer,
		                                    // const data

	char * const p3 = greeting;             // const pointer,
		                                    // non-const data

	const char * const p4 = greeting;       // const pointer,
		                                    // const data


	//
	// STL iterator are modeled after pointers, so an iterator
	// acts much like T*
	std::vector<int> v;
	v.push_back(1);

	const std::vector<int>::iterator iter = v.begin(); // iter acts like T* const

	*iter = 10;	// OK, modifies what's pointed to (value)
//	++iter;		// NO; can not modify a const iterator

	std::vector<int>::const_iterator citer = v.begin(); // citer acts like const T*
//	*citer = 100; // NO; can not modify constant value
	++citer;	  // OK: citer is not a constant pointer

	return 0;
}