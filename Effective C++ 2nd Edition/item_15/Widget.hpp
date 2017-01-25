#pragma once

class Widget
{
public:
	Widget(void);
	Widget(int, double);
	virtual ~Widget(void);

	int iParam;
	double dParam;

	Widget& operator=(const Widget& rhs);
};
