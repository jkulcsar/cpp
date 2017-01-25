#include "Widget.hpp"

Widget::Widget(void) : iParam(0), dParam(0.0)
{
}

Widget::Widget(int i, double d) : iParam(i), dParam(d)
{
}


Widget::~Widget(void)
{
}

Widget& Widget::operator =(const Widget &rhs)
{
	this->iParam = rhs.iParam;
	this->dParam = rhs.dParam;

	return *this;
}