#include <iostream>
using namespace std;

// The ONLY difference between a structure and a class is that
// members of a structure are public by default and members of 
// a class are private by default.
// Access to members of a structure can be modified by access
// modifiers.
// Structures also support inheritance, polymoprphism, etc
// just like classes.
//

struct Whatever
{
	virtual void foo() { }
	virtual ~Whatever() { }
};

struct Derived : Whatever
{
	void foo() { cout << "value " << value; }
	Derived(int n) : value(n) {
	}

private:
	int value; // private data member
};

int main()
{
	Whatever *pW  = new Derived(10);
	pW->foo(); // virtual call
	delete pW;
	return 0;
}

