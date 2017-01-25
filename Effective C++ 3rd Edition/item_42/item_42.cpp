
//
// item 42: Understand the two meanings of 'typename'
//

#include <iostream>
#include <list>

//
// when declaring template parameters,
// 'class'and 'typename' are interchangeable
//
template<class T>
class Widget;

template<typename T>
class Widget;

//
// use 'typename' to identify nested dependent type names, except:
// --- in base class lists or 
// --- as a base class identifier in a member initialization list

// example: a simple function to print the second element of a container
template<typename C>                            // print 2nd element in
void print2nd(const C& container)               // container;
{                                               // this is not valid C++!
	if (container.size() >= 2) {

		// The general rule is simple:
		// anytime you refer to a nested dependent type name in a template,
		// you must immediately precede it by the word typename. 
		typename C::const_iterator iter(container.begin());	// get iterator to 1st element
		++iter;												// move iter to 2nd element

		int value = *iter;                         // copy that element to an int
		std::cout << value;                        // print the int
		std::cout << std::endl;
	}
}

//
// There is an exception to the general rule described above:
// 'typename' is not allowed when a base class identifier
// is in a member initialization list.
// Consider this simple hierarchy:

template<typename T>
class Base
{
public:
	class Nested
	{
	public:
		explicit Nested(int) {}
	};
};

template<typename T>
class Derived : Base<T>::Nested
{
public:
	//
	// since Base<T>::Nested does not have default constructor,
	// must call it in the member initialization list

	explicit Derived(int x) : Base<T>::Nested(x)	// 'typename' NOT needed
													// since this is init. list
	{
		typename Base<T>::Nested temp_nested(x);	// 'typename' needed, using
		// ...										// a nested dependent type
	}
};

int main(int argc, char** argv)
{
	std::list<int> intList;

	for(int i = 1; i < 10; ++i)
		intList.push_back(i*i);

	print2nd(intList);

	Base<char> b;
	Derived<char> d(100);

	return 0;
}
