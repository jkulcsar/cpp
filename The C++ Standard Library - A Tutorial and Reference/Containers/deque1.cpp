#include <iostream>
#include <deque>
#include <string>
#include <algorithm>

using namespace std;

template<typename T>
void print_technical_data(const deque<T>& d)
{
	//print technical data
    cout << " max_size(): " << d.max_size() << endl;
    cout << " size():     " << d.size()     << endl;
}

template<typename T>
void print_deque_with_separator(const deque<T>& d, const char* separator)
{
	// print elements separated by spaces
	copy( d.begin(), d.end(),
		ostream_iterator<T>(cout, separator));
	cout << endl;
}


int main(int argc, char** argv)
{
	deque<string> coll;

	coll.assign(3, string("string"));
	coll.push_back("last string");
	coll.push_front("first string");

	print_deque_with_separator(coll, "\n");
	print_technical_data(coll);

	// remove first and last element
	coll.pop_front();
	coll.pop_back();
	print_deque_with_separator(coll, "\n");

	// insert "another" into every element, except the first
	for( int i=1; i < coll.size(); ++i) {
		coll[i] = "another " + coll[i];
	}
	print_deque_with_separator(coll, "\n");

	// change size to 10 elements
	coll.resize(10, "resized string");
	print_deque_with_separator(coll, "\n");
}