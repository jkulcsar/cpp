
#include <boost\signals.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

int func1()
{
	return 1;
}

int func2()
{
	return 2;
}

//Just as slots can receive arguments, they can also return values. 
//These values can then be returned back to the caller of the signal
//through a combiner. The combiner is a mechanism that can take 
//the results of calling slots (there may be no results or a hundred;
//we don't know until the program runs) and coalesces them into a single
//result to be returned to the caller. The single result is often
//a simple function of the results of the slot calls:
// -- the result of the last slot call
// -- the maximum value returned by any slot
// -- or a container of all of the results 
//are some possibilities.
//
// Here: results of the slot calls are collected in a vector
template<typename T>
struct min_element
{
	typedef T result_type;

	template<typename InputIterator>
	T operator()(InputIterator first, InputIterator last) const
	{
		return T(first, last);
	}
};

int main( int argc, char** argv )
{
	boost::signal< int (), min_element<std::vector<int> > > sig;
	sig.connect(func1);
	sig.connect(func2);
	std::vector<int> v = sig();
	std::cout << *std::min_element( v.begin(), v.end() ) << std::endl;

	return 0;
}
