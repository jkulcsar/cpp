#include <vector>
#include <deque>
#include <string>
#include <iostream>

template< typename T, template <typename ELEM> class CONT = std::deque> >
class Stack {
private:
	CONT<T> elems;	// container of elements

public:
	void push(T const&);
	void pop();
	T top() const;
	bool empty() const {
		return elems.empty();
	}
};

// member functions:
template< typename T, template <typename ELEM> class CONT> >
void Stack<T, <CONT<ELEM> >::push(T const& elem) {
	elems.push_back(elem);
}

int main(int argc, char** argv) {
	//
	// To use a different internal container for stacks, the application programmer 
	// has to specify the element type twice. Thus, to specify the type of the 
	// internal container, you have to pass the type of the container and the type 
	// of its elements again:
	//
	// Stack<int,std::vector<int> > vStack;  // integer stack that uses a vector 
	// Using template template parameters allows you to declare the Stack class template 
	// by specifying the type of the container without respecifying the type of its elements:
	//
	// stack<int,std::vector> vStack;        // integer stack that uses a vector 
}