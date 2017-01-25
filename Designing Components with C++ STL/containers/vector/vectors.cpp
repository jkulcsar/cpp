
#include <iostream>
#include <vector>

#include "../../util/container_utility.hpp"

void test_vector_of_integers()
{
	std::vector<int> intVect(10);

	for(size_t i = 0; i < intVect.size(); ++i)
		intVect[i] = i;

	// vector will increase on demand
	intVect.insert(intVect.end(), 100);

	// use vector as an array
	for(size_t i = 0; i < intVect.size(); ++i)
		std::cout << intVect[i] << "|";
	std::cout << std::endl;

	// use with an iterator
	for( std::vector<int>::iterator it = intVect.begin();
		it != intVect.end(); ++it)
		std::cout << *it << "|";
	std::cout << std::endl;

	// insert in the middle of the vector
	std::vector<int>::iterator iter = intVect.begin();
	iter += intVect.size() / 2;

	 intVect.insert( iter, 200 );
	 show (intVect);

	 // push at the end
	 intVect.push_back(13);
	 show( intVect );

	 // pop/remove from the end
	 intVect.pop_back();
	 show( intVect );

	 // erase/delete from a position (here: 2nd position)
	 iter = intVect.begin();
	 ++iter;	// move to 2nd position
	 intVect.erase(iter);  // this can also erase a range
	 show( intVect );



}

int main( int argc, char** argv )
{
	test_vector_of_integers();

	return 0;
}
