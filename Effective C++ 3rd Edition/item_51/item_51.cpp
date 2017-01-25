
//
// item 51:adhere to convention when writing new and delete

// Curiously, C++ requires that operator new return a legitimate pointer
// even when zero bytes are requested. (Requiring this odd-sounding behavior
// simplifies things elsewhere in the language.) That being the case, 
// pseudocode for a non-member operator new looks like this:
//
// things to remember:
// (1) operator new should contain an infinite loop trying to allocate memory,
// should call the new-handler if it can't satisfy a memory request, 
// and should handle requests for zero bytes. Class-specific versions 
// should handle requests for larger blocks than expected.
//
// (2) operator delete should do nothing if passed a pointer that is null.
// Class-specific versions should handle blocks that are larger than expected.


#include <memory>

//
// a pseudo-code operator new;
// operator new might take additional params
void * operator new(std::size_t size) throw(std::bad_alloc)
{                                      
	using namespace std;                

	if (size == 0) {                     // handle 0-byte requests
		size = 1;                        // by treating them as
	}                                    // 1-byte requests

	while (true) {

		//   attempt to allocate size bytes;
		//   if (the allocation was successful)
		//       return (a pointer to the memory);


		// allocation was unsuccessful; find out what the
		// current new-handling function is (see below)

		new_handler globalHandler = set_new_handler(0);
		set_new_handler(globalHandler);

		if (globalHandler) (*globalHandler)();
		else throw std::bad_alloc();
	}
}

//
// C++ guarantees it's always safe to delete the null pointer
void operator delete(void* raw_memory) throw()
{
	if(raw_memory == 0)
		return;
	
	// deallocate here the memory pointed to by raw_memory
	// ...
}


// one of the most common reasons for writing a custom memory manager 
// is to optimize allocation for objects of a specific class, not for 
// a class or any of its derived classes. That is, given an operator 
// new for a class X, the behavior of that function is typically tuned
// for objects of size sizeof(X)—nothing larger and nothing smaller.
// Because of inheritance, however, it is possible that the operator 
// new in a base class will be called to allocate memory for an object 
// of a derived class:
class Base
{
public:
	static void* operator new(std::size_t size) throw(std::bad_alloc);
	static void operator delete(void* raw_memory, std::size_t size) throw();
	// ...
};

class Derived : public Base
{
	// ...
};

void Base::operator delete(void *raw_memory, std::size_t size) throw()
{
	if (raw_memory == 0) return;           // check for null pointer

	if (size != sizeof(Base)) 
	{										// if size is "wrong,"
		::operator delete(raw_memory);		// have standard operator
		return;								// delete handle the request
	}

	//  deallocate the memory pointed to by raw_memory;
	// ...

	return;
}



int main(int argc, char** argv)
{
	Derived* p = new Derived;

	return 0;
}
