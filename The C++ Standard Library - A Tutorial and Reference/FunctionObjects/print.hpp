
#include <iostream>

template<typename T>
inline void print_collection(const T& coll, const char* opt_comment = "") {
	typename T::const_iterator pos;

	std::cout << opt_comment << std::endl;
	for(pos = coll.begin(); pos != coll.end(); ++pos) 
		std::cout << *pos << ' ';
	std::cout << std::endl;
}
