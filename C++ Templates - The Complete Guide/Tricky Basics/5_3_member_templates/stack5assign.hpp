
template <typename T>
	template <typename T2>
	Stack<T>& Stack<T>::operator=(Stack<T2> const& op2)
	{
		if((void*)this == (void*)&op2)
		{
			return *this;
		}

		//
		// this would be the more immediate implementation, however:
		// (1) op2 is const ref, we can not modify it and pop-ing 
		// removes elements which will show an error PLUS we shouldn't
		// destroy the stack referenced by op2
		// solution: like below, create a local copy;
		// a bit expensive but for stacks is the only way
		// (2) because through pop-ing we get the elements in reverse
		// order, we use push_front to re-create the stack as it was
		//
		//while(!op2.empty()) {
		//	elems.push_front(op2.top());
		//	op2.pop();
		//}

		// create local copy; we can't modify the incoming ref
		Stack<T2> tmp(op2);

		// clear the existing elements
		elems.clear();

		// push to the front, because we're getting the elements
		// in reverse order
		while(!tmp.empty()) {
			elems.push_front(tmp.top());
			tmp.pop();
		}

		return *this;
	}
