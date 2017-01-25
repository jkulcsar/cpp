
#include <iostream>
#include <vector>

#include "..\ESTLUtil_rewrite.hpp"
#include "..\Widget.h"


int main(int argc, char** argv) {
	std::vector<int> v;

	for(int i = 0; i < 10; ++i)
		v.push_back(i);

	printContainer(v);

	return 0;
}