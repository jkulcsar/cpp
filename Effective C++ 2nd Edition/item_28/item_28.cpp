#include <iostream>
using namespace std;

namespace sdm {
	const double BOOK_VERSION = 2.0;

	class Handle {
	};

	Handle& getHandle();
}


//
// clients can access symbols in 3 ways:
// (1) by importing all the symbols in a namespace into a scope
// (2) by importing	individual symbols into a scope
// (3) by explicitly qualifying a symbol for one time use
//

void f1() {
	using namespace sdm;
	cout << BOOK_VERSION << endl;	// OK, resolves to sdm::BOOK_VERSION
}

void f2() {
	using sdm::BOOK_VERSION;
	cout << BOOK_VERSION << endl; //OK, individual symbol name imported into
			// the scope of this function
}

void f3() {
	cout << sdm::BOOK_VERSION << endl; //OK, fully qualifyed symbol name
}


int main(int argc, char** argv)
{
	f1();
	f2();
	f3();

	return 0;
}