
#include <iostream>
#include <string>
#include <cstdint>
#include "boost/lexical_cast.hpp"

//
// generic programming with boost::lexical_cast
// here: a function template
template <typename T> std::string to_string(const T& arg) {
	try {
		return boost::lexical_cast<std::string>(arg);
	}
	catch(boost::bad_lexical_cast& e) {
		// don't re-throw the exception
		// just return an empty string on failure
		return "";
	}
}


//
// Enabling Classes for Use with lexical_cast
//
// Because lexical_cast only requires that operator<< and operator>> be 
// suitably defined for the types it operates on, it's straightforward 
// to add support for lexical conversions to user-defined types. 
// A simple UDT that can be both the target and source when used with 
// lexical_cast might look like this:
//
class lexical_castable {
public:
	lexical_castable() {}
	lexical_castable(const std::string s) : s_(s) {};

	friend std::ostream& operator<< (std::ostream& o, const lexical_castable& le);
	friend std::istream& operator>> (std::istream& i, lexical_castable& le);
private:
	virtual void print_(std::ostream& o) const {
		o << s_;
	}

	virtual void read_(std::istream& i) {
		i >> s_;
	}

	std::string s_;
};

// definition of the friend operator<< and operator>>
std::ostream& operator<< (std::ostream& o, const lexical_castable& le) {
	le.print_(o);
	return o;
}

std::istream& operator>> (std::istream& i, lexical_castable& le) {
	le.read_(i);
	return i;
}

template <typename ElemT>
struct HexTo {
	ElemT value;
	operator ElemT() const {return value;}
	friend std::istream& operator>>(std::istream& in, HexTo& out) {
		in >> std::hex >> out.value;
		return in;
	}
};


int main() {
	// string to int
	std::string s = "42";
	int i = boost::lexical_cast<int>(s);

	// float to string
	float f = 3.141592;
	s = boost::lexical_cast<std::string>(f);

	// literal to double
	double d = boost::lexical_cast<double>("2.52");

	try	{
	uint16_t ui16 = boost::lexical_cast<HexTo<uint16_t> >("0x2A");
	uint8_t ui8 = (uint8_t) ui16; // yes, downcast from a short (16bit) int!
	}
	catch(boost::bad_lexical_cast& e) {
		std::cout << e.what() << std::endl;
	}


	// failed conversion
	s = "not an int";
	try {
		i = boost::lexical_cast<int>(s);
	}
	catch(boost::bad_lexical_cast& e) {
		std::cout << e.what() << std::endl;
	}

	//
	// test drive the generic 'to_string' function
	// defined above
	std::string str = to_string(412);
	std::cout << str << std::endl;
	
	str = to_string(2.357);
	std::cout << str << std::endl;

	//
	// use the lexical_castable class defined earlier
	lexical_castable le;
	std::cout << "Enter a number to initialize a lexical_castable object: ";
	std::cin >> le;

	try {
		int i = boost::lexical_cast<int>(le);
		std::cout << "i cast from le is now: " << i << std::endl;
	}
	catch(boost::bad_lexical_cast&) {
		std::cout << "You were supposed to enter a number!" << std::endl;
	}

	return 0;
}
