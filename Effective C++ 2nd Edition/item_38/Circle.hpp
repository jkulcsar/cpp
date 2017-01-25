#pragma once
#include <iostream>
#include "Shape.hpp"

class Circle :
	public Shape
{
public:
	Circle(void);
	virtual ~Circle(void);
	virtual void draw(ShapeColor color) const {
		using namespace std;
		cout << "Circle::draw() color = " << color << endl;
	}
};
