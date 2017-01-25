
#include <iostream>

//
// in C++ even an empty class has size, typically 1 byte
class EmptyClass {
};

int main(int argc, char** argv)
{
	std::cout << "sizeof(EmptyClass): " << sizeof(EmptyClass) << std::endl;

	return 0;
}