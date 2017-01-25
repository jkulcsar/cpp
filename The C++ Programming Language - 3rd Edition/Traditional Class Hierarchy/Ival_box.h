#pragma once

class Ival_box
{
protected:
	int val;
	int low, high;
	bool changed;
public:
	Ival_box(int ll, int hh)
	{
		changed = false;
		val = low = ll;
		high = hh;
	}

	virtual int get_value() 
	{
		changed = false;
		return val;
	}

	virtual void set_value(int i)
	{
		changed = true;
		val = i;
	}

	virtual void prompt() {}

	virtual bool was_changed() const
	{ 
		return changed; 
	}
};
