
//
// item 30: Make sure destination ranges are big enough

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <functional>
#include <algorithm>
#include <iterator>

#include "../ESTLUtil_rewrite.hpp"
#include "../Widget.h"

using namespace std;


int transmogrify(int x) {
	return ++x;
}

int main(int argc, char** argv) {
	vector<int> v_source;
	vector<int> v_target;

	for(int i = 0; i < 10; ++i)
		v_source.push_back(i);

	//
	// trying to use transform algo which has an empty target collection!
	// v_target.end() is invalid, the following code will crash

	//transform(
	//	v_source.begin(),
	//	v_source.end(),
	//	v_target.end(),
	//	transmogrify
	//	);

	//
	// solution: use inserters!
	// here: back_inserter
	transform(
		v_source.begin(),
		v_source.end(),
		back_inserter(v_target),
		transmogrify
		);

	//
	// here: using inserter to insert new elements in the middle of the
	// target collection
	transform(
		v_source.begin(),
		v_source.end(),
		inserter(v_target, v_target.begin() + v_target.size() / 2),
		transmogrify
		);
	printContainer(v_target);

	return 0;
}