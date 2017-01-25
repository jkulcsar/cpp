

#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include "boost/any.hpp"

bool is_int(const boost::any& a) {
	return typeid(int) == a.type();
}

bool is_string(const boost::any& a) {
	return typeid(std::string) == a.type();
}

// template version of the previous two functions!
template<typename T>
bool contains(const boost::any& a) {
	return typeid(T) == a.type();
}

//
// counting non-empty values
class any_counter {
	int count_;
public:
	any_counter() : count_(0) {}

	int operator() (const boost::any& a) {
		return a.empty() ? count_ : ++count_;
	}

	int count() {
		return count_;
	}
};

class A {
};

int main(int argc, char** argv) {

	std::vector<boost::any> v;

	boost::any a1(std::string("Just a string!"));
	boost::any a2;
	boost::any a3(200);
	boost::any a4;
//	boost::any a5(A());

	v.push_back(a1);
	v.push_back(a2);
	v.push_back(a3);
	v.push_back(a4);
	v.push_back(A());


	int c = std::for_each(v.begin(), v.end(), any_counter()).count();
	std::cout << "Non-empty elements in this collection: " << c << std::endl;

	// Note that the for_each algorithm returns the function object, 
	// so we can easily access the count. Because for_each accepts its 
	// arguments by value, the following code does not accomplish the same thing.
	any_counter counter;
	std::for_each(v.begin(),v.end(),counter);
	int i=counter.count();
	std::cout << "Wrong way of using predicates: " << std::endl <<
		 "Non-empty elements in this collection: " << i << std::endl;

	//
	// finish this example of using predicates!
	//

	return 0;
}