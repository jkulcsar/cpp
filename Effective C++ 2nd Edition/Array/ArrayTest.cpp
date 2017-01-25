#include "Array.hpp"

class Simple
{
};

class SimpleNoDefault
{
public:
	SimpleNoDefault(int i) {};
};

int main(int argc, char** argv) {
	Array<double> ad1(10);
	Array<double> ad2(ad1);

	Array<Simple> as(10);

	// error: SimpleNoDefault has no default constructor
	// when new is called for an array, it calls the default ctor for each element
//	Array<SimpleNoDefault> asnd(10); 

	return 0;
}