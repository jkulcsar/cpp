
#include <iostream>
#include "basememberpair.hpp"
//
// EBCO - empty base class optimization
// even though in C++ there are no non-zero sized types, the C++ standard
// specifies that when an empty class is used as base class no space needs
// to be allocated for it provided that it does not cause it to be allocated
// to the same address as another object or sub-object of the same type


class Empty {
	// typedef members don't make a class non-empty
	typedef int Int;
};

class EmptyToo : public Empty {
};

class EmptyThree : public EmptyToo {
};

class NonEmpty : public Empty, public EmptyToo {
};

class AnotherEmpty {
};

//
// even if T1 and T2 are empty classes, no optimization
// is applied, essentially wasting memory for every instance
// of type MyClass
template <typename T1, typename T2>
class MyClass {
private:
	T1 a;
	T2 b;
	// ...
};

template <typename CustomClass> 
class Optimizable { 
  private: 
    BaseMemberPair<CustomClass, void*> info_and_storage; 
    // ...
}; 


int main(int argc, char** argv)
{
	std::cout << "sizeof(Empty): " << sizeof(Empty) << std::endl;
	std::cout << "sizeof(EmptyToo): " << sizeof(EmptyToo) << std::endl;
	std::cout << "sizeof(EmptyThree): " << sizeof(EmptyThree) << std::endl;
	std::cout << "sizeof(NonEmpty): " << sizeof(NonEmpty) << std::endl;
	std::cout << std::endl;
	std::cout << "sizeof(MyClass<Empty, EmptyToo>): " << sizeof(MyClass<Empty, EmptyToo>) << std::endl;
	std::cout << "sizeof(MyClass<Empty, AnotherEmpty>): " << sizeof(MyClass<Empty, AnotherEmpty>) << std::endl;
	std::cout << std::endl;
	std::cout << "sizeof(Optimizable<Empty>): " << sizeof(Optimizable<Empty>) << std::endl;
	std::cout << "sizeof(Optimizable<EmptyThree>): " << sizeof(Optimizable<EmptyThree>) << std::endl;

	return 0;
}