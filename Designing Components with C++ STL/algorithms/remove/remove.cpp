#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include <cstring>

#include "../../util/container_utility.hpp"
#include "../../util/iota.hpp"

bool isVowel(char c)
{
	return std::strchr("aeiouAEIOU", c) != 0;
}

int main(int argc, char** argv)
{
	std::vector<char> v(26);
	br_stl::iota(v.begin(), v.end(), 'a');
	
	std::ostream_iterator<char> Output(std::cout, "");
	std::copy( v.begin(), v.end(), Output );
	std::cout << std::endl;

	std::cout << "removing 't' :" << std::endl;
	std::vector<char>::iterator last = 
		std::remove( v.begin(), v.end(), 't' );
	// the iterator 'last' is now the new end, after shifting
	// v.end() remains unchanged but it's invalid!
	std::copy( v.begin(), last, Output );
	std::cout << std::endl;

	// let's show that v.end() remains unchanged but it's invalid!
	std::copy( v.begin(), v.end(), Output );
	std::cout << std::endl;

	last = std::remove(v.begin(), last, isVowel );
	std::cout << "only consonants left: " << std::endl;
	std::copy( v.begin(), last, Output );
	std::cout << std::endl;

	return 0;
}
