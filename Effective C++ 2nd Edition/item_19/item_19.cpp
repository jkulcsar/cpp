#include "Rational.hpp"

//
//Virtual functions must be members. If f needs to be virtual, make it a member function of C. 
//
//operator>> and operator<< are never members. If f is operator>> or operator<<, 
//make f a non-member function. If, in addition, f needs access to non-public members of C, 
// make f a friend of C. 
//
//Only non-member functions get type conversions on their left-most argument. 
//If f needs type conversions on its left-most argument, make f a non-member function.
//If, in addition, f needs access to non-public members of C, make f a friend of C. 
//
//Everything else should be a member function. If none of the other cases apply, 
//make f a member function of C. 
//

int main(int argc, char** argv[])
{
	Rational oneEight(1,8);
	Rational oneHalf(1,2);

	Rational result = oneEight * oneHalf;

	result = oneEight * 2;

//	result = 2 * oneHalf; // this won't work, there is no operator* 
							// for primitive data types (here: int)


	// only works if operator * is non-member, allowing compilers 
	// to perform implicit type conversion on all arguments:

	result = 2 * oneHalf;

	return 0;
}