
#include <iostream>
#include <string>
#include <cstdlib>
#include "stack5.hpp"

int main(int argc, char** argv) {
	try {
		Stack<int> intStack;	// stack of integers
		Stack<float> floatStack;	// stack of floats

		intStack.push(44);
		intStack.push(7);

		floatStack.push(7.7);

		// assign stacks of different type
		floatStack = intStack;

		// show
		std::cout << floatStack.top() << std::endl;
		floatStack.pop();
		std::cout << floatStack.top() << std::endl;
		floatStack.pop();
		std::cout << floatStack.top() << std::endl;
		floatStack.pop();
	}
	catch(std::exception const& ex) {
		std::cerr << "Exception: " << ex.what() << std::endl;
		return EXIT_FAILURE;	// exit program with ERROR status
	}
	return 0;
}