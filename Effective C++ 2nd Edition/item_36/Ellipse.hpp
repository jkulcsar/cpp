#pragma once
#include "shape.hpp"

class Ellipse :
	public Shape
{
public:
	Ellipse(void);
	virtual ~Ellipse(void);
	virtual void draw() const;
};
