#include "Rectangle.hpp"
#include "Ellipse.hpp"

#include "Airport.hpp"
#include "ModelA.hpp"

int main(int argc, char** argv) {

//	Shape *ps = new Shape;           // error! Shape is abstract
	
	Shape *ps1 = new Rectangle;      // fine
	ps1->draw();                     // calls Rectangle::draw
	
	Shape *ps2 = new Ellipse;        // fine
	ps2->draw();                     // calls Ellipse::draw
	
	ps1->Shape::draw();              // calls Shape::draw
	ps2->Shape::draw();              // calls Shape::draw

	Airport jfk("JFK");
	ModelA ma;
	ma.fly(jfk);

	Airport sfo("SFO");

	//
	// try to copy an Airport into another - doesn't make sense
	// so don't do it and protect against it by declaring copy ctor
	// and assignement op private (or protected)
	//
	// jfk = sfo;
	// Airport yyz(jfk);

	//
	// bottom line of this item:
	// use/provide a default implementation (definition)
	// for pure virtual functions; it's possible, it's elegant
	// so use it.
	//

	return 0;
}