#include "Shape.hpp"

Shape::Shape(void)
{
}

Shape::~Shape(void)
{
}
void Shape::draw() const {
	//
	// It is possible to provide a definition for a pure virtual function.
	// That is, you could provide an implementation for Shape::draw, 
	// and C++ wouldn't complain, but the only way to call it would be 
	// to fully specify the call with the class name: 
	// Shape::draw()
	//
	// implementation here...
	//
}
void Shape::error(const string& message) {
	//
	// implementation here...
	//
}

int Shape::objectID() const {
	//
	// implementation here...
	//
	return id_;
}
