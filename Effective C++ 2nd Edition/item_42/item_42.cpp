
#include "IntStack.hpp"
#include "CatStack.hpp"
#include "..\Stack\Stack.hpp"

//
// item 42: Private inheritance means: is-implemented-in-terms-of
//

int main( int argc, char** argv) {
	IntStack_v1 is_v1;
	CatStack_v1 cs_v1;

	int i1 = 10;
	int i2 = 11;
	is_v1.push(&i1);
	is_v1.push(&i2);

	Cat c1, c2, c3;
	Cat *pc5;
	cs_v1.push(&c1);
	cs_v1.push(&c2);
	cs_v1.push(&c3);
	pc5 = cs_v1.pop(); // will point to the c3 object !

	//
	// since all interface functions are public,
	// nothing can stop us from instantiating such an object
	// the user than has full control over the control of the
	// pointer type, exactly what we wanted to avoid
	GenericStack_v1 gs_v1;
	gs_v1.push(static_cast<void*>(pc5));

//	GenericStack gs; // can not instantiate, even contructor is not public
	// only type-safe version can be instantiated:

	IntStack is;
	is.push(&i1);
	int i = * is.pop();

	CatStack cs;
	cs.push(&c2);
	cs.push(&c1);
	Cat c = * cs.pop();

	//
	// more generic solution
	Stack<Cat> gen_cs;
	gen_cs.push(c1);
	gen_cs.push(c2);
	gen_cs.push(c3);

	return 0;
}