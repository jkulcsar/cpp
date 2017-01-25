#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>

#include "../../util/container_utility.hpp"

// a simple function to be used by the generate() algorithm
int PowerOfTwo()
{
	static int Value = 1;
	return (Value *= 2) / 2;
}

// a functor to be passed in to the generate() algorithm
class Random
{
	int range;
public:
	Random(int r) : range(r) {}

	int operator()()
	{
		return (int) ( (double)rand() * range / (RAND_MAX+1.0) );
	}
};

bool test_generate_with_functor( const Random& r, std::vector<int>& v )
{
	std::generate( v.begin(), v.end(), r );

	return true;
}

bool test_generate_with_simple_function(std::vector<int>& v)
{
	std::generate_n(v.begin(), v.size() - 2, PowerOfTwo );
	return true;
}

int main(int argc, char** argv)
{
	Random random_fctor(1000);
	std::vector<int> lottery(12);

	test_generate_with_functor( random_fctor, lottery );
	show(lottery);

	test_generate_with_simple_function( lottery );
	show(lottery);

	return 0;
}
