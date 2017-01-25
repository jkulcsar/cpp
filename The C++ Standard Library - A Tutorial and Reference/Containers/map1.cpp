#include <iostream>
#include <map>
#include <string>
#include "newkey.hpp"

using namespace std;
using namespace lib::cpp::edu;

template<typename Cont>
void print_map(const Cont& coll)
{
	Cont::const_iterator pos;
	for(pos = coll.begin(); pos != coll.end(); ++pos)
		cout << "key: " << pos->first << "\t" << "value: " << pos->second << endl;
	cout << endl;
}

int main( int argc, char** argv )
{
	map<string, double> m1;

	m1.insert(make_pair("otto", 22.3));
	m1.insert(make_pair("john", 12.8));
	m1.insert(make_pair("george", 11.9));

	print_map(m1);

	replace_key(m1, "george", "henry");

	print_map(m1);


	return 0;
}