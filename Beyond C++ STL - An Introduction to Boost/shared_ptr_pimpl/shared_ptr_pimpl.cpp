

// The Pimpl Idiom Revisited
// The pimpl idiom was previously presented in conjunction with scoped_ptr, 
// which works well as a means of storing the dynamically allocated instance 
// of the pimpl, if copying is not permitted for the class using the idiom. 
//
// That is not appropriate for all classes that would benefit from using 
// the pimpl idiom (note that scoped_ptr can still be used, but copy 
// construction and assignment need to be implemented by hand). 
// For those classes that can handle shared implementation details, 
// shared_ptr comes into play. When ownership of the pimpl is passed to a 
// shared_ptr, the copying and assignment operators come for free. 
// You'll recall that when using scoped_ptr to handle the lifetime 
// of the pimpl class, copying of the outer class is not allowed, 
// because scoped_ptrs are not copyable. This means that to support 
// copying and assignment in such classes, a copy constructor and 
// assignment operator must be defined manually. When using shared_ptr 
// to handle the lifetime of the pimpl, a user-defined copy constructor 
// may not even be needed. Note that the pimpl instance will be shared 
// among the objects of the class, so if there is state that only applies 
// to one instance of the class, a handcrafted copy constructor is still 
// required.
//
// The solution is very similar to what we saw for scoped_ptr; 
// just make it a shared_ptr, instead.
//

#include "pimpl_sample.hpp"

int main(int argc, char** argv)
{
	{
		pimpl_sample s1, s2;
		s1.do_something();
		s2.do_something();

		s1.setvalue("This is s1.");
		s1.do_something();
		s2.do_something();

		s2 = s1;
		s1.do_something();
		s2.do_something();


		pimpl_sample s3("This is another pimpl.");
		s2 = s3;
		s3.do_something();
		s2.do_something();
	}

	return 0;
}
