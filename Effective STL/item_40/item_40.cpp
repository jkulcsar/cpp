

//
// item 40: Make functor classes adaptable.

// Adaptable means make "certain typedefs" available; most used are
// argument_type, first_argument_type, second_argument_type, and result_type
//

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <functional>
#include <algorithm>
#include "../Widget.h"

using namespace std;

bool isInteresting(const Widget* pw) {
	return pw->getVal() % 2 == 0;	// interesting == even
}


//In both cases, notice how the types passed to unary_function or binary_function are
//the same as the types taken and returned by the functor class's operator!), though it is a
//bit of an oddity that operator's return type is passed as the last argument to
//unary_function or binary_function.

template<typename T>
class MeetsThreshold : public unary_function<Widget, bool> {
private:
	const T threshold_;
public:
	MeetsThreshold(const T& threshold) : threshold_(threshold) {}
	bool operator()(const Widget& w) const {
		return w.getVal() >= threshold_;
	}
	// ...others
};

struct WidgetNameCompare : binary_function<Widget, Widget, bool> {
	bool operator()(const Widget& lhs, const Widget& rhs) const {
		return lhs.getVal() <= rhs.getVal();
	}
};

//
// doesn't need to derive from binary_function 
template <typename T>
struct WidgetCompare : binary_function<T, T, bool> {
	bool operator()(const T& lhs, const T& rhs) const {
		return lhs <  rhs; // calls op<() of Widget
	}
};

int main(int argc, char** argv)
{
//	typedef vector<Widget>::iterator VectorWidgetIter;	// helper typedef
	list<Widget*> widgetPtrs;

	// add a few Widgets to the vector
	for(int i = 0; i<10; ++i) {
		widgetPtrs.push_back(new Widget(i));
	}

	// find the first Widget pointer that's 'interesting' (here: has even val)
	list<Widget*>::iterator i = find_if(
		widgetPtrs.begin(),
		widgetPtrs.end(),
		isInteresting
		);
	if(i != widgetPtrs.end()) {
		// process first 'interesting' pointer-to-widget
		cout << "first Widget found has: " << (*i)->getVal() << endl;
	}

	// now, find the first Widget pointer that's NOT 'interesting' (here: has odd val)
	//list<Widget*>::iterator in = find_if(
	//	widgetPtrs.begin(),
	//	widgetPtrs.end(),
	//	not1(isInteresting)	// ERROR! won't compile
	//	);
	//if(in != widgetPtrs.end()) {
	//	// process first 'interesting' pointer-to-widget
	//	cout << "first Widget found has: " << (*in)->getVal() << endl;
	//}

	// find the first Widget pointer that's NOT 'interesting' (here: has even val)
	list<Widget*>::iterator in = find_if(
		widgetPtrs.begin(),
		widgetPtrs.end(),
		not1(ptr_fun(isInteresting))	// must apply ptr_func first!
		);
	if(in != widgetPtrs.end()) {
		// process first 'interesting' pointer-to-widget
		cout << "first Widget found has: " << (*in)->getVal() << endl;
	}

	list<Widget> widgets;

	widgets.push_back(Widget(13));
	widgets.push_back(Widget(25));
	widgets.push_back(Widget(3));
	widgets.push_back(Widget(30));
	widgets.push_back(Widget(40));
	widgets.push_back(Widget(50));

	list<Widget>::reverse_iterator rev_it = find_if(
		widgets.rbegin(),
		widgets.rend(),
		not1(MeetsThreshold<int>(10)) // type param is type of the threshold param
		);

	if(rev_it.base() != widgets.end() )
		cout << "Last widget failing to meet the threshold is: " << *rev_it << endl;
	else
		cout << "All widgets meet the threshold!" << endl;

	cout << "size of widgetPtrs is: " << widgetPtrs.size() << endl;


	//set<Widget, WidgetNameCompare> customSortedSetOfWidgets;
	set<Widget, WidgetCompare<Widget> > customSortedSetOfWidgets;
	
	customSortedSetOfWidgets.insert(Widget(13));
	customSortedSetOfWidgets.insert(Widget(25));
	customSortedSetOfWidgets.insert(Widget(33));
	customSortedSetOfWidgets.insert(Widget(30));
	customSortedSetOfWidgets.insert(Widget(40));
	customSortedSetOfWidgets.insert(Widget(50));

	set<Widget, WidgetCompare<Widget> >::iterator iter = customSortedSetOfWidgets.begin();
	while( iter != customSortedSetOfWidgets.end() )
	{
		cout << *iter << std::endl;
		++iter;
	}

	return 0;
}
