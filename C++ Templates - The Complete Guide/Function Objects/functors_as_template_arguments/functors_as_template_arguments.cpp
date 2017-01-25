
#include <iostream>
#include <functional>

template<typename FO>
void my_sort() {
	// create function object
	FO cmp;

	if( cmp(x,y) ){
		//...
	}
}



int main(int argc, char** argv) {

	// call function with functor
	my_sort<std::less<int> >();
	return 0;
}
