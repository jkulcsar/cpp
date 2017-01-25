#pragma once
#include <iostream>
#include "Shape.hpp"

class Rectangle :
	public Shape
{
public:
	Rectangle(void);
	virtual ~Rectangle(void);
	virtual void draw(ShapeColor color = GREEN) const {
		using namespace std;
		cout << "Rectangle::draw() color = " << color << endl;
	}
};
