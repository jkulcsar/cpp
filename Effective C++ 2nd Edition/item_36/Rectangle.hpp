#pragma once
#include "shape.hpp"

class Rectangle :
	public Shape
{
public:
	Rectangle(void);
	virtual ~Rectangle(void);
	virtual void draw() const;
};
