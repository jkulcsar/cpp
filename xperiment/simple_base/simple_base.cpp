
#include <iostream>
class A {
	int i_;
public:
	A(int i = 0) : i_(i) {
		std::cout << "In A() ctor" << std::endl;
	}
	virtual ~A() {
		std::cout << "In ~A() dtor" << std::endl;
	}
};

class B : public A {
	double d;
public:
	B() {
		std::cout << "In B() ctor" << std::endl;
	}
	virtual ~B() {
		std::cout << "In ~B() dtor" << std::endl;
	}
};


int main(int argc, char** argv)
{
	A* pa = new B;

	if(pa)
		delete pa;

	return 0;
}
