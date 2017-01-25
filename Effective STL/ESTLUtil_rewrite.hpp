
// ESTLUtil_rewrite.hpp
// As the filename suggests this is a step-by-step rewrite
// of the original ESTLUtil.h file; this helps in understanding
// some of the implementation details in the original util file.

#ifndef ESTLUTILS_REWRITE_HPP
#define ESTLUTILS_REWRITE_HPP

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <ctime>

//
// print a non-pointer value
template<typename T>
struct printValue {
	void operator()(const T& value, std::ostream& s = std::cout) {
		s << value;
	}
};

//
// print a pointed-to-value
template<typename T>
struct printValue<T*> {
	void operator()(const T* pValue, std::ostream& s = std::cout) {
		s << *pValue;
	}
};

//
// print a container
template<typename Container>
void printContainer(const Container& c, std::ostream& s = std::cout) {
	using namespace std;

	//for(typename Container::const_iterator b = c.begin();
	//	b != c.end();
	//	++b) {
	//		printValue<Container::value_type>()( *b );
	//		s << ' ';
	//}

	for_each(
		c.begin(),
		c.end(),
		printValue<Container::value_type>()
		);

	s << endl;
}

#endif