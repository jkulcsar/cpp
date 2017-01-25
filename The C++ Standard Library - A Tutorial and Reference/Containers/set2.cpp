#include <iostream>
#include <set>

using namespace std;

int main(int argc, char** argv)
{
	set<int> c;

	c.insert(1);
	c.insert(2);
	c.insert(4);
	c.insert(5);
	c.insert(6);

	// lower_bound returns the first position where the element with the 
	// passed value would be inserted
	// using de-referncing to get the value at that location
	cout << "lower_bound(3) : " << *c.lower_bound(3) << endl;

	// upper_bound returns the position of the first element 
	// with a greater value than the argument
	cout << "upper_bound(3) : " << *c.upper_bound(3) << endl;

	// equal_range returns the range where the values in the set 
	// are the same as the value passed as the argument
	// here: if the pair has equal values, there is no element with value 
	// passed in as argument
	cout << "equal_range(3) : " << *c.equal_range(3).first << " " << *c.equal_range(3).second << endl;

	cout << "equal_range(4) : " << *c.equal_range(4).first << " " << *c.equal_range(4).second << endl;
}