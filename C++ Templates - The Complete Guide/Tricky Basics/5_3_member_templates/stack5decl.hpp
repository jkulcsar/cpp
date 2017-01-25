//
// do not include std libraries here, this is just a template
// declaration, included in another header file
//#include <deque>

template <typename T>
class Stack {
private:
	std::deque<T> elems;	// elements container

public:
	void push(T const&);	// push element
	void pop();				// pop element
	T top() const;			// return top element
	bool empty() const {
		return elems.empty();
	}

	// assignement operator
	// assign stack of elements of T2
	template <typename T2>
	Stack<T>& operator=(Stack<T2> const&);
};