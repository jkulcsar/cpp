
//
// item 26: Prefer iterator to const_iterator, reverse_iterator and const_reverse_iterator

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <functional>
#include <algorithm>
#include "../Widget.h"

using namespace std;



int main(int argc, char** argv)
{
	typedef deque<int> IntDeque;
	typedef IntDeque::iterator Iter;
	typedef IntDeque::const_iterator CIter;

	Iter i;
	CIter ci;

	// instantiate a container
	IntDeque d;
	for(int i = 0; i < 10; ++i)
		d.push_front(i);

	// init the iterators to the beginning of container
	i = d.begin();
	ci = d.begin();

	if( i == ci )
		cout << "Iterators are equal." << endl;
	else
		cout << "Iterators are not equal." << endl;

	if (ci == i)								// workaround for when the 
		cout << "Iterators are equal." << endl;	// comparison above won't compile
	else
		cout << "Iterators are not equal." << endl;	

	
	if (ci + 3 <= i)							// workaround for when the above
		cout << "Iterators are equal." << endl;	// won't compile
	else
		cout << "Iterators are not equal." << endl;	


	return 0;
}