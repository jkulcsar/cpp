#pragma once

enum ShapeColor { RED, GREEN, BLUE };
class Shape
{
public:
	Shape(void);
	virtual ~Shape(void);
	void virtual draw(ShapeColor color = RED) const = 0;
};
