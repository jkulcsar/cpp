#include <iostream>
#include <boost/bind.hpp>

void F2( int i, float f )
{
	std::cout << "i: " << i << std::endl;
	std::cout << "f: " << f << std::endl;
}

int main( int argc, char * argv[] )
{
	boost::bind( &F2, 42, 3.14f )();
	return 0;
}