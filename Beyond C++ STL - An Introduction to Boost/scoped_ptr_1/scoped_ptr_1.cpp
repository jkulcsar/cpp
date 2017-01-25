#include "boost/scoped_ptr.hpp"
#include <string>
#include <iostream>

void scoped_vs_auto() 
{
	using boost::scoped_ptr;
	using std::auto_ptr;

	scoped_ptr<std::string> p_scoped(new std::string("Hello"));
	auto_ptr<std::string> p_auto(new std::string("Hello"));

	p_scoped->size();
	p_auto->size();

	//
	// the following line won't compile because scoped_ptr can not be
	// copy-constructed or assigned to
//	scoped_ptr<std::string> p_another_scoped = p_scoped;
//	p_another_auto->size();	

	//
	// for auto_ptr, assignement is OK
	// but means transfer of ownership! (see below)
	auto_ptr<std::string> p_another_auto = p_auto;

	//
	// this results in undefined behavior at runtime, 
	// because of dereferencing the null pointer in p_auto (*p_auto);
	// now p_another_auto owns the pointer
//	(*p_auto).size();
	(*p_another_auto).size();
}

int main() {
	{
		boost::scoped_ptr<std::string> 	p(new std::string("Use scoped_ptr often."));

		// Print the value of the string
		if (p)
			std::cout << *p << '\n';

		// Get the size of the string
		size_t i=p->size();

		// Assign a new value to the string
		*p="Acts just like a pointer";

		scoped_vs_auto();

	} // p is destroyed here, and deletes the std::string 
}
