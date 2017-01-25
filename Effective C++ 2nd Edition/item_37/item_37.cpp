
#include "SimpleBase.hpp"
#include "SimpleDerived.hpp"

int main(int argc, char** argv) {
	SimpleDerived d;

	SimpleBase* pb = &d;
	SimpleDerived* pd = &d;

	//
	// non-virtual member functions are statically bound
	// the type of the pointer matters, NOT the type of
	// the objects these pointer point to:
	// since the object is of type SimpleDerived, all calls
	// to simple_mf() SHOULD go to SimpleDerived; they will not,
	// instead these will be routed depending on the type of the
	// pointer
	//
	pb->simple_mf();
	pd->simple_mf();

	//
	// virtual functions however are dynamically bound;
	// only the type of the object they point to matters!
	// here: always the SimpleDerived::virtual_mf() will be called.
	//
	pb->virtual_mf();
	pd->virtual_mf();

	//
	// bottom line: never re-define non-virtual functions
	// to avoid unexpected behavior due to the different type of the
	// pointer to the object
	//

	return 0;
}