
//
// item 39: Make predicates pure functions.

// predicate: is a function that returns bool

// pure function: a function whose return value depends only on its parameters
// If f is a pure function and x and y are objects, the return value of f(x,y)
// can change only if the value of x or y changes.

// predicate class: a functor whose operator() function returns bool.

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <functional>
#include <algorithm>
#include <iterator>

#include "../Widget.h"

using namespace std;


	// A predicate is a function that returns bool (or something that can be implicitly
	// converted to bool). Predicates are widely used in the STL. The comparison
	// functions for the standard associative containers are predicates, and predicate
	// functions are commonly passed as parameters to algorithms like find_if and the
	// various sorting algorithms. (For an overview of the sorting algorithms, turn to
	// Item 31.)
	//
	// A pure function is a function whose return value depends only on its
	//parameters. If f is a pure function and x and y are objects, the return value of
	//f(x, y) can change only if the value of x or y changes.
	//

class BadPredicate : public unary_function<Widget, bool> {
public:
	BadPredicate() : timesCalled(0) {}
	bool operator()(const Widget&) {
		return ++timesCalled == 3;
	}
private:
	size_t timesCalled;
};

//
// accepts the current object and the current index (calculated by std::distance)

class GoodPredicate : public binary_function<Widget, size_t, bool> {
public:
	GoodPredicate( size_t n) : index_(n) {}
	bool operator()(const Widget&, const size_t current_index) const 
	{
		return current_index == index_;
	}
private:
	size_t index_;
};

int main(int argc, char** argv)
{
	typedef vector<Widget>::iterator VectorWidgetIter;	// helper typedef
	vector<Widget> vw;

	// add a few Widgets to the vector
	for(int i = 0; i<10; ++i) {
		vw.push_back(Widget(i));
	}

	cout << "size of vw is: " << vw.size() << endl;

	// eliminate the 3rd Widget
	// however this will eliminate not just the 3rd but also the 6th element
	// because the erase algotithm uses a copy of the BadPredicate functor;
	// to avoid problems like this, just stick to the pure function rule
	// outlined above
	vw.erase( 
		remove_if(	vw.begin(),	vw.end(), BadPredicate()),
		vw.end() );

	cout << "size of vw is: " << vw.size() << endl;

	//
	// this is not a good solution!
	// there is no way to know the current index as the remove_if algorithm proceses
	// the elements in the container
	vw.erase( 
		remove_if(	vw.begin(),	vw.end(), GoodPredicate(3).operator()(std::distance() ),
		vw.end() );
		
	cout << "size of vw is: " << vw.size() << endl;

	return 0;
}