#pragma once
#include "ival_box.h"

class Ival_dial :
	public Ival_box
{
public:
	Ival_dial(int ll, int hh) : Ival_box(ll, hh) {};
public:
//	int get_value();

	void prompt()
	{
		set_value(100);
	}
};
