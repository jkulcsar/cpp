
#include <iostream>
#include <vector>

using namespace std;

class Base {
public:
	void f1() {
		cout << "Base::f1()" << endl;
	}
	void f2() {
		cout << "Base::f2()" << endl;
	}
};

class Derived : public Base {
public:
	void f1() {
		cout << "Derived::f1()" << endl;
	}
	void f2() {
		cout << "Derived::f2()" << endl;
	}
};

class Another {
public:
	void f1() {
		cout << "Another::f1()" << endl;
	}

	void f3() {
		cout << "Another::f3()" << endl;
	}
};

////////////////////////////////////////////////////////
class Top {
public:
	Top(int i) : i_(i) {}
private:
	int i_;
};

class Bottom : public Top {
public:
	// Top has no default ctor generated ->
	// the following implies a call to
	// default ctor and it fails
//	Bottom(int i) {}

	// to call explicitly the ctor needed:
	Bottom(int i) : Top(i) {
	}
};
////////////////////////////////////////////////////////


int main( int argc , char** argv )
{
	//
	// Base and Another are unrelated,
	// no polymorphic behavior, must explicitly
	// use reinterpret_cast
	//
	Another* a = new Another();
	Base* b = reinterpret_cast<Base*> (new Another());
	b->f1();

	//
	// polymorphic behavior
	// dynamic_cast is not even really needed
	// since (or, if) RTTI is available
	//
	Derived* d = new Derived();
	Base* bb = dynamic_cast<Base*> (d);
	bb->f1();
	Base* bbb = d;
	bbb->f1();

	return 0;
}