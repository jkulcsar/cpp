//
// Covariant returns
// A long-standing C++ rule requires that a member function that overrides a virtual 
// function must have not only the same signature but also the same return value as 
// the base class member function. In the following code, for example, A::f and B::f 
// both return a pointer to an object of class X:
//

class X {};

class A
{
public:
    virtual X* f() {return new X;}
};
//
//class B : public A
//{
//public:
//    virtual X* f() {return new X;}
//};

// In real-world object models, however, it is quite common for B::f to want to return a 
// pointer to an object derived from X. Standard C++ allows such covariant returns, 
// so you can modify the code as follows:

class Y : public X {};

class B : public A
{
public:
    virtual Y* f() {return new Y;}
};

int main(int argc, char** argv)
{
	B b;
	Y*  py = b.f();

	if(py)
		delete py;

	return 0;
}