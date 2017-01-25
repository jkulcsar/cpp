
//
// itercat.cpp
#include <vector>
#include <iostream>

using namespace std;


//
// This example won't work with lists, sets, and maps because all 
// operations that are marked with NOTE: are provided only for 
// random access iterators. In particular, keep in mind that you 
// can use operator < as an end criterion in loops for random access
// iterators only.
//

int main(int argc, char **argv)
{
	vector<int> coll;

	// insert elements from -3 to 9
	for(int i = -3; i <= 9; ++i)
		coll.push_back(i);

	// print number of elements by processing the distance between
	// beginning and end of the collection
	// NOTE: uses operator- for iterators
	cout << "number of elements, calculated as distance: "
		<< coll.end() - coll.begin()
		<< endl;

	// iterator to parse the collection
	vector<int>::iterator pos;

	// print all elements
	// NOTE: using operator < instead of !=
	for(pos=coll.begin(); pos<coll.end(); ++pos)
		cout << *pos << " ";
	cout << endl;

	// print all elements
    // NOTE: uses operator [ ] instead of operator *
	for (int i=0; i<coll.size(); ++i) {
		cout << coll.begin() [i] << ' ';
	}
	cout << endl;

	// print every second element
	// NOTE: uses operator +=
	for(pos=coll.begin(); pos<coll.end()-1; pos+=2)
		cout << *pos << " ";
	cout << endl;

	return 0;
}