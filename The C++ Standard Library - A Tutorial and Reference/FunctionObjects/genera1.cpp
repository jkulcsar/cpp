#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

#include "print.hpp"

using namespace std;

class IntSequence {
public:
	IntSequence(int v) : value_(v) {
	}

	// "function call"
	int operator() () {
		return value_++;
	}
private:
	int value_;
};

int main(int argc, char** argv) {
	list<int> coll;

	// insert values from 1 to 9
	generate_n(
		back_inserter(coll),	// start
		9,						// number of elements
		IntSequence(1));		// generates values

	print_collection(coll, "Sequence of integers: ");

	// replace second to last-but-one element with values starting at 42
	generate(
		++coll.begin(),			// start
		--coll.end(),			// end
		IntSequence(42));		// generates values
	
	print_collection(coll, "Sequence of integers (after replacement): ");

	return 0;
}