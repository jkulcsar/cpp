#include "Airplane.hpp"

Airplane::Airplane(void)
{
}

Airplane::~Airplane(void)
{
}

//
// provide a default implementation (definition)
// for the pure virtual function fly;
// this avoids using an extra function i.e. defaultFly()
// which is called as the first step in the fly()
// functions of different airplane models;
// this is a.k.a. eliminating namespace pollution by
// introducing several functions with closely related names
// and functionality
//

void Airplane::fly(const Airport& destination) {
	//
	// sequence of events common to flying each plane
	//
}
