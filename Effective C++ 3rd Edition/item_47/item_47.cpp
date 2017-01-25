
//
// item 47: use traits classes for information about types
//
// This chapter discusses traits in context of STL iterators and these
// are used as an example.
// Goal of this mini project: re-implement the advance() algorithm of STL
// using traits of iterators to make compile-time decisions.
//

#include <iterator>

// the following includes are needed only for the example code to work
#include <list>
#include <vector>
#include <string>

//
// input and output iterators: These are the two least powerful iterator categories.
// Because input and output iterators can move only forward and can read or 
// write what they point to at most once, they are suitable only 
// for one-pass algorithms.
//
// (1) input iterators:  (best example is istream_iterator)
// - can only move forward
// - can only move one step at a time
// - can only READ what they point to
// - can only READ it only once
//
// (2) output iterators: (best example is ostream_iterator)
// - can only move forward
// - can only move one step at a time
// - can only WRITE what they point to
// - can only WRITE it only once
//
// (3) 
// - FIXME: continue this review and add it to the "Designing components with STL" iterator project(s)


//
// design choices for re-implementing advance():
// - we can use the lowest common denominator strategy of all iterator classes,
// that is using a loop that iteratively increments/decrements the iterator.
// But this takes linear time.
// Random access iterators support constant-time arithmetic so let's use it.
//
//


template<typename IterT>
struct iterator_traits
{
	typename IterT::iterator_category iterator_category;
	//...
};

//
// specialization for pointers;
// pointers are essentially random-access iterators
template<typename IterT>
struct iterator_traits<IterT*>
{
	typedef std::random_access_iterator_tag iterator_category;
	//...
};


//
// this is a simple implementation of advance();
// note that is using a conditional determination, based on the type
// of the iterator; this can be avoided by factoring out the actual
// logic and base it solely on it's type then let the compiler determine
// which one to instantiate based on function overloading rules
template< typename IterT, typename DistT>
void advanceUsingConditional(IterT& iter, DistT d)
{
	// check first if it is a random access iterator
	if( typeid(typename std::iterator_traits<IterT>::iterator_category) ==
		typeid(std::random_access_iterator_tag) )
	{
		iter += d;
	}
	// use iterative calls to increment/decrement iterator categories
	else
	{
		if( d >= 0 )
		{
			while(d--)
				++iter;
		}
		else
		{
			while(d++)
				--iter;
		}
	}
}

//
// use this implementation for random access iterators
template<typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d,
	std::random_access_iterator_tag)
{
	iter += d;
}

//
// use this implementation for bidirectional iterators
template<typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d,
	std::bidirectional_iterator_tag)
{
	if( d >= 0 )
	{
		while(d--)
			++iter;
	}
	else
	{
		while(d++)
			--iter;
	}
}

//
// use this implementation for input iterators
template<typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d,
	std::input_iterator_tag)
{
	if( d < 0 )
	{
		throw std::out_of_range("Negative distance");
	}

	while(d--)
		++iter;
}

//
// a better implementation of advance():
// uses function overloading so the doAdvance() called is being determined
// at compile time;
// this is huge: avoids using if/else statements on looking up the type
// of the iterators; always only the 'right' doAdvance() is instantiated,
// based on function overload rules!
//
template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d)
{
	doAdvance(
		iter, d,
		typename std::iterator_traits<IterT>::iterator_category()
		);
}

int main(int argc, char** argv)
{
	//
	// using a regular pointer as iterator
	// NOTE! For delete[] to work on the pointer it must be reset/rewound
	// to it's initial position!
	char* p = new char[10];
	advance(p, 3);
	char c = *p;
	::advance(p, -3);

	delete[] p;

	//
	// use it on a list
	// std::list has bidirectional iterators
	std::list<char> abcList;
	for(size_t i = 0; i < 26; ++i)
		abcList.push_back('a' + i);

	std::list<char>::iterator abc_iter = abcList.begin();
	::advance( abc_iter, 10);
	c = *abc_iter;

	//
	// use it on a vector
	// std::vector supports random access iterators
	std::vector<char> abcVector;
	for(size_t i = 0; i < 26; ++i)
		abcVector.push_back('a' + i);

	std::vector<char>::iterator abc_vector_iter = abcVector.begin();
	::advance( abc_vector_iter, 11 );
	c = *abc_vector_iter;

	return 0;
}
