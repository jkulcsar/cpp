
#include <iostream>
#include "boost/cast.hpp"
#include "boost/limits.hpp"

int main() {
	std::cout << "larger_to_smaller example" << std::endl;

	// Conversions without numeric_cast
	long l = std::numeric_limits<short>::max();

	short s = l;
	std::cout << "s is: " << s << std::endl;
	s = ++l;
	std::cout << "s is: " << s << std::endl << std::endl;

	// Conversions with numeric_cast
	try {
		l = std::numeric_limits<short>::max();
		s = boost::numeric_cast<short>(l);
		std::cout << "s is: " << s << std::endl;
		s = boost::numeric_cast<short>(++l);
		std::cout << "s is: " << s << std::endl;
	}
	catch(boost::bad_numeric_cast& e) {
		std::cout << e.what() << std::endl;
	}
}
