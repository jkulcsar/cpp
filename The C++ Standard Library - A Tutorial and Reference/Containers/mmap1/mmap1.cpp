
#include <iostream>
#include <string>
#include <map>
#include <iomanip>

int main(int argc, char** argv) {
	using namespace std;

	typedef multimap<string, string> StrStrMap;

	StrStrMap dict;

	//insert some elements in random order
	dict.insert(make_pair("day","Tag"));
	dict.insert(make_pair("strange","fremd"));
	dict.insert(make_pair("car","Auto"));
	dict.insert(make_pair("smart","elegant"));
	dict.insert(make_pair("trait","Merkmal"));
	dict.insert(make_pair("strange","seltsam"));
	dict.insert(make_pair("smart","raffiniert"));
	dict.insert(make_pair("smart","klug"));
	dict.insert(make_pair("clever","raffiniert"));

	//print the dictionary; use some formatting
	StrStrMap::iterator pos;

	cout.setf(ios::left, ios::adjustfield);
cout << ' ' << setw(10) << "english "
            << "german " << endl; 
       cout << setfill('-') << setw(20) << "" << setfill(' ') << endl;
       for (pos = dict.begin(); pos != dict.end(); ++pos) {
           cout << ' ' << setw(10) << pos->first.c_str()
                << pos->second << endl;
       }
       cout << endl;


	return 0;
}