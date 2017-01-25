
#include <iostream>
#include <string>
#include "boost/variant.hpp"

//
// The function "print" does its job correctly now, but what if we decide to 
// change the set of types for the variant? Then we will have introduced
// a subtle bug that won't be caught at compile time; the function print 
// will not print the value of any other types than the ones we've originally 
// anticipated. If we hadn't used a template function, but required an exact 
// signature of a variant, we would risk proliferation of overloads 
// to accommodate the same functionality for different types of variants. 
// The next section discusses the concept of visiting variants, 
// and the problem that (typesafe) visitation solves.
//


template<typename V>
void print(V& v) {
	if(int* pi = boost::get<int>(&v))
		std::cout << "it's an int: " << *pi << std::endl;
	else if(std::string* ps = boost::get<std::string>(&v))
		std::cout << "it's a string: " << *ps << std::endl;
	else if(double* pd = boost::get<double>(&v))
		std::cout << "it's a double: " << *pd << std::endl;

	std::cout << "printing is done!" << std::endl;
}

class print_visitor : public boost::static_visitor<void> {
public:
	void operator()(int& i) const {
		std::cout << "\t visitor says: it's an int: " << i << std::endl;
	}
	void operator()(std::string& s) const {
		std::cout << "\t visitor says: it's a string: " << s << std::endl;
	}
	void operator()(double& d) const {
		std::cout << "\t visitor says: it's a double: " << d << std::endl;
	}
};

// Note that if the call to get fails (which would happen if the variant didn't contain
// a value of type int), an exception of type boost::bad_get is thrown. To avoid getting 
// an exception upon failure, we can pass a pointer to a variant to get, in which case 
// get returns a pointer to the value or, if the requested type doesn't match the type 
// of the value in the variant, it returns the null pointer.
template<typename V>
void demonstrate_exception_on_wrong_type(V& v) {
	//
	// check for type char in this variant
	// (should not be there)
	try {
		assert(boost::get<char>(v)=='a');
	}
	catch(boost::bad_get& e) {
		std::cout << e.what() << std::endl;
	}

	try {
		char* value = boost::get<char>(&v);
		assert(!value);
	}
	catch(boost::bad_get& e) {
		std::cout << e.what() << std::endl;
	}
}

int main(int argc, char** argv) {
	boost::variant<int, std::string, double>
		my_first_variant("Hello there!");
	print_visitor visitor;

	demonstrate_exception_on_wrong_type(my_first_variant);

	print(my_first_variant);
	boost::apply_visitor(visitor, my_first_variant);

	my_first_variant = 12;
	print(my_first_variant);
	boost::apply_visitor(visitor, my_first_variant);

	my_first_variant = 3.14;
	print(my_first_variant);
	boost::apply_visitor(visitor, my_first_variant);

	my_first_variant = 'a';
	print(my_first_variant);
	boost::apply_visitor(visitor, my_first_variant);


	return 0;
}
