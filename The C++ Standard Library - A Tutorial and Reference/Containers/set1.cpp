#include <iostream>
#include <set>

using namespace std;

int main(int argc, char** argv)
{
	//
	// type of the collection:
	//  - no duplicates
	//  - elements are integral values
	//  - descending order
	typedef set<int, greater<int> > IntSet;

	IntSet coll1;

	//insert elements in random order
	coll1.insert(4);
	coll1.insert(3);
	coll1.insert(5);
	coll1.insert(1);
	coll1.insert(6);
	coll1.insert(2);
	coll1.insert(5);

	// iterate over all elements 
	IntSet::iterator pos;
	for(pos = coll1.begin(); pos != coll1.end(); ++pos)
		cout << *pos << " " ;
	cout << endl;





}