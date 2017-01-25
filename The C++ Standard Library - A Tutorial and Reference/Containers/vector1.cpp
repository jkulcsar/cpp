
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

template<typename T>
void print_technical_data(const vector<T>& v)
{
	//print ''technical data''
    cout << " max_size(): " << v.max_size() << endl;
    cout << " size():     " << v.size()     << endl;
    cout << " capacity(): " << v.capacity() << endl;
}

template<typename T>
void print_vector_with_separator(const vector<T>& v, const char* separator)
{
	// print elements separated by spaces
	copy( v.begin(), v.end(),
		ostream_iterator<T>(cout, separator));
	cout << endl;
}

int main( int argc, char** argv)
{
	// create a vector for strings
	vector<string> sentence;

	// reserve memory for 5 elements to avoid re-allocation
	sentence.reserve(5);

	// append some elements
	sentence.push_back("Hello,");
	sentence.push_back("how");
    sentence.push_back("are");
    sentence.push_back("you");
    sentence.push_back("?");

	// print elements separated by spaces and some technical data
	print_vector_with_separator(sentence, " ");
	print_technical_data(sentence);
    
	// swap second and fourth element
	// unchecked:
	// swap(sentence[1], sentence[3]);
	// checked:
	try	{
		swap(sentence.at(1), sentence.at(3));
	}
	catch(out_of_range e) {
		cout << "exception:" << e.what() << endl;
	}

	// insert "always" in front of "?"
	sentence.insert(find(sentence.begin(), sentence.end(), "?"),
					"always");

	//assign "!" to the last element
    sentence.back() = "!";

	// print elements separated by spaces and some technical data
	print_vector_with_separator(sentence, " ");
	print_technical_data(sentence);
	
	//
	// use std::find to look for a specific element
	std::string search_this("you");
	vector<string>::iterator it = std::find(sentence.begin(), sentence.end(), search_this);
	if(it!= sentence.end())
		std::cout << *it << std::endl;
	return 0;
}