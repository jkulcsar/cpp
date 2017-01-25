#include <iostream>
#include <memory>

class Base
{
private:
	int	base_i_;
protected:
	double base_d_;
	double doSomethingWithBaseD() { 
		return base_d_;
	}
public:
	int getBaseInt() {
		return base_i_;
	}
	void setBaseInt(int i) {
		base_i_ = i;
	}

	double getBaseDouble() {
		return base_d_;
	}

	void setBaseDouble(double d) {
		base_d_ = d;
	}

	Base(int i = 0, double d = 0.0) : base_i_(i), base_d_(d) {}
};

class Derived : public Base
{
public:
	void f(int i, double d) {
		//
		// ERROR: try to access directly a private member of base class
		// base_i_ = i;
		// instead, use setter fct:
		setBaseInt(i);

		//
		// OK: try to access directly protected member of base class
		base_d_ = d;
	}

};

int main(int argc, char** argv)
{
	using namespace std;
	Base b;

	auto_ptr<Base> pB(new Base(1, 10.0));
	auto_ptr<Derived> pD(new Derived());
	double d_val = pD->doSomethingWithBaseD();

	return 0;
}