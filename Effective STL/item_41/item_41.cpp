#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

//
// Using mem_fun
// And a great example of binding a class member function,
// in a polymorphic situation

// the all-classic shape hierarchy
class shape {
public:
	virtual void draw() const
	{
		std::cout << "shape::draw()" << std::endl;
	}
};

class circle : public shape {
public:
	virtual void draw() const
	{
		std::cout << "circle::draw()" << std::endl;
	}
};

class square : public shape {
public:
	virtual void draw() const
	{
		std::cout << "square::draw()" << std::endl;
	}
};

int main(int argc, char** argv)
{
	//  Assemble a vector of shapes
	circle c;
	square s;
	std::vector<shape*> v;
	v.push_back(&s);
	v.push_back(&c);

	// Using mem_fun is the simplest way to access any polymorphic
	// charateristics of an object held in a standard container;
	// in this example: call draw on each one
	std::for_each(v.begin(), v.end(), std::mem_fun(&shape::draw));

	return 0;
}
