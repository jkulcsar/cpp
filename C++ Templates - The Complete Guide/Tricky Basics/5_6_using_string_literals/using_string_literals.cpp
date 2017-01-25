#include <string>
#include <iostream>

//
// For string literals there is an array-to-pointer conversion during argument 
// deduction if and only if the parameter is not a reference.
//


// note: reference parameters
template<typename T>
inline T const& max_ref(T const& a, T const& b) {
	return a < b ? b : a;
}

// note: non-reference parameters
template<typename T>
inline T max_non_ref(T a, T b) {
	return a < b ? b : a;
}

template<typename T>
void ref(T const& x) {
	std::cout << "x in ref(T const&): " <<
		typeid(x).name() << std::endl;
}

template<typename T>
void nonref(T x) {
	std::cout << "x in nonref(T): " <<
		typeid(x).name() << std::endl;
}

int main(int argc, char** argv) {
	std::string s;

//	::max_ref("apple", "peach");	// OK: exactly the same type
//	::max_ref("apple", "tomato");	// ERROR: different types
//	::max_ref("apple", s);			// ERROR: different types

	::max_non_ref("apple", "peach");	// OK: exactly the same type
	::max_non_ref("apple", "tomato");	// now is OK: decays to same type
//	::max_non_ref("apple", s);			// ERROR: different types

	// clear illustration of ref vs. nonref template function usage:
	ref("hello");
	nonref("hello");
}

