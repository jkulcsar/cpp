
#include <iostream>
#include <string>
#include "boost/any.hpp"


int main(int argc, char** argv) {
	std::cout << "Example of using 'any' member functions." << std::endl;

	boost::any a1(100);
	boost::any a2(std::string("200"));
	boost::any a3;

	std::cout << "a3 is ";
	if(!a3.empty())
		std::cout << "not ";
	else
		std::cout << "empty!" << std::endl;

	a1.swap(a2);

	try {
		std::string str = boost::any_cast<std::string>(a1);
		std::cout << "a1 contains a string: " << str << std::endl;
	}
	catch(boost::bad_any_cast& e) {
		std::cout << "any_cast problems: " << e.what() << std::endl;
	}

	if( int* p = boost::any_cast<int>(&a2))
		std::cout << "a1 seems to have swaped content with a2: " << *p << std::endl;
	else
		std::cout << "Nope, no int in a2!" << std::endl;

	if(typeid(int) == a2.type()) {
		std::cout << "a2's type_info equals the type_info of int" << std::endl;
	}

	return 0;
}