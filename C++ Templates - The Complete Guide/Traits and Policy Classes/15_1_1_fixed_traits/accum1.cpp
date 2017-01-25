
#include <iostream>

//
// determining the type of the return value based on the parameter type
// is important; accum1.hpp does not differentiate, uses same type for
// return as is the type of the input parameters
//#include "accum1.hpp"

//
// in accum2, we define a new type for the type of the return value;
// this is called a traits template because it holds a trait of its 
// parameter type;
// here, two solutions could be used:
// (1) introduce another template parameter to specify the return type
// (2) or (used here) create an association between each type T for which
// accum() could be called and the corresponding type that should hold
// the type of the return value;
// this association can be considered a characteristic of the type T, hence
// the name 'trait of T'
// solution: this association can be encoded as specializations of a template
//
#include "accum2.hpp"

int main()
{
	// create an array of integers
	int num[] = {1,2,3,4,5};

	// print average value
	std::cout << "average value: " 
		<< accum(&num[0], &num[5]) / 5
		<< std::endl;

	// now create an array of character values
	char name[] = "templates";
	int length = sizeof(name) - 1;

	// print the average character value
	std::cout << "the average value of the character values in / " 
		<< name << " / is: "
		<< accum(&name[0], &name[length]) / length
		<< std::endl;
}