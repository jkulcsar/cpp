
//
// item 38: Design functor classes for pass-by-value

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <functional>
#include <algorithm>
#include "../Widget.h"

#include <boost/shared_ptr.hpp>

using namespace std;

// see item 46 why using the STL sort algorithm is better than
// using qsort function
// here: cmpfcn is a pointer-to-function however this is passed in
// by value, it's copied
// this is representative for the rule followed by the standard libraries
// for both C and C++, namely, that pointers to functions are passed in
// by value
void qsort(void* base, size_t noOfElems, size_t sizeOfElem,
		   int (*cmpfcn)(const void*, const void*));



class DoSomething : public unary_function<int, void>	// Item 40 explains base class
{
public:
	void operator()(int x) {
		cout << "In DoSomething::operator(), x = " << x << endl;
	}
	// ...
};

/*
template<typename T>
class BPFC : public unary_function<T, void>  { // Item 40 explains base class
private:
	// this class has lots of data, so it would be
	// inefficient to pass it by value
	Widget w;
	int x;
	// ... other data members here
public:
	// this is a virtual function, so 'slicing' would be bad
	virtual void operator()(const T& val) const;
	// ...
};
*/

template<typename T>
class BPFCImpl {
private:
	// all the data that used to be in BPFC
	Widget w;
	int x;
	// ... other data members here


	virtual void operator()(const T& val) const {
		cout << "in functor call with param: " << val << endl;
	}
	template<typename T> friend class BPFC;	// let BPFC access the data
public:
	virtual ~BPFCImpl() {}	// polymorphic classes need virtual destructors
};

//
// create a small, monomorphic class that contains a pointer to an
// implementation class and put all the data and virtual functions
// in the implementation class
template<typename T>
class BPFC : public unary_function<T, void> {
private:
//	BPFCImpl<T>* pImpl;
	boost::shared_ptr< BPFCImpl<T> > pImpl;
public:
	BPFC() : pImpl(new BPFCImpl<T>()) {
	}
	~BPFC() {
		//
		// internally, STL may create more copies of the functor objects
		// this means multiple destructions of the underlying pImpl;
		// that's not what we want: there's a one-to-one realtionship
		// between the wrapper class and the pImpl; so we need to check
		// if the pImpl was not already deleted
		//if( pImpl ) {
		//	delete pImpl;
		//	pImpl = 0;
		//}
	}

	// The implementation of BPFC::operator() exemplifies how all BPFC would-be virtual
	// functions are implemented: they call their truly virtual counterparts in BPFCImpl. The
	//result is a functor class (BPFC) that's small and monomorphic, yet has access to a
	//large amount of state and acts polymorphically.
	void operator()(const T& val) const {
		pImpl->operator()(val);
	}
};



int main(int argc, char** argv)
{
	typedef deque<int>::iterator DequeIntIter;	// helper typedef
	deque<int> di;

	// add a few elements
	di.push_back(10);
	di.push_front(9);

	DoSomething d;

	// call for_each with type parameters DequeIntIter and a
	// reference to the function object; this will force passing
	// 'd' by reference; in this case it is not recommended
	// function objects should be always passed by value!
	//for_each<DequeIntIter, DoSomething&>(di.begin(), di.end(), d);
	for_each( di.begin(), di.end(), d);

	typedef vector<string >::iterator StringVectorIt;
	vector<string> str_v;
//	BPFC<string> bpfc;
	
	str_v.push_back("this_is_one");
	str_v.push_back("this_is_two");
//	for_each<StringVectorIt, BPFC<string> >(
	for_each(
		str_v.begin(),
		str_v.end(),
		BPFC<string>() );



	
	return 0;
}