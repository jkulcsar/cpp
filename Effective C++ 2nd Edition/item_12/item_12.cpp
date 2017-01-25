#include "NamedPtr.hpp"
#include "NamedPtr2.hpp"


int main( int argc, char* argv[] )
{
	int myInt = 0;
	double myDouble = 0;
	double anotherDouble = 3.14;

	NamedPtr<int> simple("myInt", &myInt);
	NamedPtr2<double> complex("myDouble", &myDouble);
	NamedPtr2<double> another_complex("anotherDouble", &anotherDouble);
	complex = another_complex;

	return 0;
}