
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "boost/any.hpp"

class any_property {
	std::string name_;
	boost::any value_;

public:
	any_property(
		const std::string& name, 
		const boost::any& value) :
	name_(name), value_(value) {}

	 std::string name() const {
	  return name_;
	 }

	 boost::any& value() {
	  return value_;
	 }

	friend bool operator< (const any_property& lhs,
		const any_property& rhs) {
			return lhs.name_ < rhs.name_;
	}
};

void print_names_values(any_property& p) {
	std::cout << p.name() << " : ";
	try {
		//
		// the if() statements verify if casting the 'any' object
		// yields a valid pointer; if it does, perform another cast,
		// returning a reference to the value;
		// in case no suitable cast is found the exception will catch it

		if(boost::any_cast<std::string>(&p.value()))
			std::cout << boost::any_cast<std::string>(p.value()) << std::endl;
		else
			if(boost::any_cast<double>(&p.value()))
				std::cout << boost::any_cast<double>(p.value()) << std::endl;
			else
				if(boost::any_cast<int>(&p.value()))
					std::cout << boost::any_cast<int>(p.value()) << std::endl;
	}
	catch(boost::bad_any_cast&)
	{
		std::cout << "Bad 'any' cast found!" << std::endl;
	}
}

int main(int argc, char** argv) {
	std::cout << "Example of using boost::any for storing properties." 
		<< std::endl;

	std::vector<any_property> properties;

	properties.push_back(any_property("B", 30));
	properties.push_back(any_property("A", std::string("Thirty something")));
	properties.push_back(any_property("C", 3.141592));

	std::sort(properties.begin(),properties.end());
	// will call operator< (friend) defined earlier

	std::for_each(properties.begin(), properties.end(), print_names_values);



	return 0;
}

