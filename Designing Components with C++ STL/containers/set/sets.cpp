
#include <iostream>
#include <set>

#include "../../util/container_utility.hpp"

typedef std::set<int> intSet_type;

template< typename set_type >
void union_of_sets( const set_type& s1, const set_type& s2, set_type& result )
{
	set_type temp_set(s2);

	if( &s1 != &s2 ) // this is a quick check to see if the two sets are actually not the same!
	{
		typename set_type::const_iterator cit = s1.begin();
		while( cit != s1.end() )
			temp_set.insert(*cit++);
	}

	temp_set.swap(result);
}

template< typename set_type >
void intersection_of_sets( const set_type& s1, const set_type& s2, set_type& result )
{
	set_type temp_set;
	typename set_type::const_iterator cit1 = s1.begin(), cit2;

	while( cit1 != s1.end() )
	{
		cit2 = s2.find(*cit1++);
		if( cit2 != s2.end() )
			temp_set.insert(*cit2);
	}
	temp_set.swap(result);
}

void test_union_of_sets()
{

	intSet_type S1, S2, S3;
	// fill lists with sorted numbers
	for(int i = 0; i < 10; ++i) {
		S1.insert(2*i);		// even numbers
		S2.insert(2*i+1);	// odd numbers
	}
	show(S1);
	show(S2);

	union_of_sets( S1, S2, S3 );
	show(S1);
	show(S2);
	show(S3);

}

void test_intersection_of_sets()
{
	intSet_type S1, S2, S3;
	// fill lists with sorted numbers
	for(int i = 0; i < 10; ++i) {
		S1.insert(2*i);		// even numbers
		S2.insert(2*i+1);	// odd numbers
	}
	show(S1);
	show(S2);

	// add a few common elements so we can see an intersection
	S1.insert( *(++S2.begin()) );
	S1.insert( *(--S2.end()) );
	S2.insert( *(++S1.begin()) );

	intersection_of_sets( S1, S2, S3 );
	show(S1);
	show(S2);
	show(S3);

}


int main( int argc, char** argv )
{
	test_union_of_sets();
	test_intersection_of_sets();

	return 0;
}
