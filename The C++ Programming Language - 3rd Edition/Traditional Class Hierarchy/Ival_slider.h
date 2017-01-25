#pragma once
#include "Ival_box.h"

class Ival_slider :	public Ival_box
{
public:
	Ival_slider(int ll, int hh) : Ival_box(ll, hh) {};
public:
//	int get_value();
	void prompt()
	{
		set_value(200);
	}
};
