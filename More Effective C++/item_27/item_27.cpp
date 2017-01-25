
//
// Item 27: Requiring or prohibiting heap-based objects

#include "UPNumber.hpp"
int main(int argc, char **argv)
{
	//
	// using UPNumber objects

	using namespace UPN;

//	UPNumber n;		// compile errors since it tries to call the 
					// destructor which is private

	UPNumber *pn = new UPNumber();	// fine

//	delete pn;		// compile error, dtor is private

	pn->destroy();	// fine

	return 0;
}