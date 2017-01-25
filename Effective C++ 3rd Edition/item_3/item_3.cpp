#include <vector>
#include <iostream>

//
// Declaring something const helps compilers detect usage errors. const can be applied to 
// objects at any scope, to function parameters and return types, and to member functions as a whole.
//
// Compilers enforce bitwise constness, but you should program using conceptual constness.
//
// When const and non-const member functions have essentially identical implementations,
// code duplication can be avoided by having the non-const version call the const version.
//



//
// just an empty class
class Widget {
};

void f1( const Widget *pW ) {
	// const data, the object pointed to by pW can not be modified
	// (f1 takes a pointer to a constant Widget object)
}

void f2( Widget const *pW ) {
	// const data, f2 also takes a pointer to a constant Widget object
}

//
// const member functions:
// purpose of const member functions are to identify which functions
// may be invoked on const objects of this type; in other words, const
// member functions can not modify the state of the object

class TextBlock {
	char * text;
public:
	TextBlock(char* t) {
		text = t;
	}

	// ...
	const char& operator[](std::size_t position) const { // operator[] for const objects
		return text[position];
	}

	// return a reference to the character at position, not just a copy of the character!
	char& operator[](std::size_t position) {		// operator[] for non-const objects
		return text[position];
	}
};

int main(int argc, char ** argv) {

	//
	// if 'const' is on the left of the * then what's pointed to (the data) is const (can not be modified)
	// if 'const' is on the right of the * then the pointer is constant 
	// (is not allowed to point to something else) but the data is not constant (can be modified)
	//
	char greeting[] = "Hello";
	char *p1 = greeting;				// non-const pointer, non-const data
	const char *p2 = greeting;		// non-const pointer, const data (what's pointed to)
	char * const p3 = greeting;		// const pointer, non-const data
	const char * const p4 = greeting;	// const ponter, const data

	greeting[0] = 'Y';				// OK to modify 
	std::cout << greeting << std::endl;

	p1[0] = 'H';					// OK to modify
	std::cout << p1 << std::endl;

	//p2[0] = 'Y'; // not OK to modify, data is constant

	p3[0] = 'Y'; // OK to modify data, but...
//	p3++; // ... not OK to modify the pointer itself

	// there's no way to modify p4 or through p4: both data and pointer itself
	// are constant; so let's just view it:
	std::cout << p4 << std::endl;

	// STL ierators are modeled on pointers
// "iterator" acts much like T* pointer:
// (1) "iterator const" is just like declaring T* const: the iterator can not point to something else
// but the data it points to can be modified
// (2) "const_iterator" is analogue of "const T*": the data it points to can not be modified.

	std::vector<int> v;
	v.push_back(1);
	const std::vector<int>::iterator iter = v.begin();
//	std::vector<int>::iterator const iter = v.begin();
	*iter = 10; 
//	++iter; // error; iter is const

	std::vector<int>::const_iterator cIter = v.begin();
	for(cIter; cIter!=v.end(); ++cIter) {		// OK, changes cIter
//		*cIter = 10; // error, data con not be modified
	}

//
	// using TextBlock
	TextBlock tb("Hello");
	std::cout << tb[0] << std::endl;		// call non-const TextBlock::operator[]

	const TextBlock ctb("World");
	std::cout << ctb[0] << std::endl;


//
	// index in Stroustrup book
//	const 94
//Cstyle
//string and 90
//and linkage 199
//and overloading 600
//casting away 414
//function, inspector 706
//iterator 443
//member 249
//member function 229
//physical and logical 231
//pointer 96
//pointer to 96
//constant
//expression 833
//inclass
//definition of 249
//member 249
//time 464
//constantexpression
//0 835
//const_cast 131, 232
//const_iterator 54, 443, 480
//basic_string 583
//const_mem_fun1_ref_t 518, 521
//const_mem_fun1_t 518, 521
//const_mem_fun_ref_t 518, 521
//const_mem_fun_t 518, 521
//const_pointer 443
//basic_string 583
//const_reference 443, 480
//basic_string 583
//const_reverse_iterator 443, 480
//basic_string 583
	return 0;
}