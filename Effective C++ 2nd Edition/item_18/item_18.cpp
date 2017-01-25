#include "MinimalArray.hpp"

#include <iostream>

int main( int argc, char* argv[] )
{
	MinimalArray<int> ma(10, 20);

	//
	// make an array of squares
	for(int i = ma.lowBound(); i < ma.highBound(); ++i)
		ma[i] = i * i;

	//
	// 
	for(int i = ma.lowBound(); i < ma.highBound(); ++i)
		std::cout << "[" << i << "] = " << ma[i] << std::endl;

	return 0;
}