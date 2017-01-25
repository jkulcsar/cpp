
#include <vector>
#include "printcoll.hpp"

int main(int argc, char** argv) {
	std::vector<int> intVec;

	for(int i = 10; i >=0; --i)
		intVec.push_back(i);

	printcoll<std::vector<int> >(intVec);
}
