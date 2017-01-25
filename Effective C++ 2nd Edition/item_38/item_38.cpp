#include "Circle.hpp"
#include "Rectangle.hpp"

int main(int argc, char** argv) {

	// an object's static type is the type declared to have
	// in the program text
	//
	// the static type of the following pointer is Shape*
	// it makes absolutely no difference what they're really
	// pointing to, their static type does not change
	//
	Shape *ps;
	Shape *pc = new Circle;
	Shape *pr = new Rectangle;

	//
	// virtual functions are dynamically bound;
	// meaning that the particular function called is
	// determined by the type of the dynamic object
	// through which is invoked;
	// dynamic types can change, i.e. through assignement:
	ps = pc;
	pc->draw();	// calls Circle::draw(RED)
	ps->draw();

	ps = pr;
	pr->draw();	// calls Rectangle::draw(RED)
	ps->draw();

	// virtual functions are dynamically bound
	// while default parameters are statically bound;
	// here: even if Rectangle::draw() uses GREEN as default,
	// since it's called through a Shape* static type, always
	// the default param of Shape::draw() will apply,
	// which is RED

	return 0;
}