

#include <iostream>
#include <list>
#include <algorithm>

#include "../../../util/container_utility.hpp"

void test_merging_sorted_lists()
{
	typedef std::list<int> intList_type;
	intList_type L1, L2;
	// fill lists with sorted numbers
	for(int i = 0; i < 10; ++i) {
		L1.push_back(2*i);		// even numbers
		L2.push_back(2*i+1);	// odd numbers
	}
	show(L1);
	show(L2);

	// now merge the two lists;
	// the first list is the target/result of the merge
	L1.merge(L2);
	show(L1);
	show(L2);

	// task:
	// insert using splice into the first list all elements
	// from the second list between 5 and 13;
	// first, we need to re-create the values in the second list;
	// these have been removed merged into the first list
	for(int i = 0; i < 10; ++i)
		L2.push_back(2*i+1);	// odd numbers

	// find the range in the second list
	intList_type::iterator start_in_L2 = std::find( L2.begin(), L2.end(), 5 );
	intList_type::iterator end_in_L2 = std::find( L2.begin(), L2.end(), 13 );
	L1.splice(
		++L1.begin(),
		L2,
		start_in_L2,
		end_in_L2 );
	show(L1);
	show(L2);

}

void test_list_operations()
{
}

int main( int argc, char** argv )
{
	test_list_operations();
	test_merging_sorted_lists();

}