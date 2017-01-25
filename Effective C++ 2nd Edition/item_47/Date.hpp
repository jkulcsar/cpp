#pragma once

class Date
{
	int d, m, y;
	static Date default_date;
public:
	Date(int dd = 0, int mm = 0, int yy = 0);
	// others...
	static void set_default(int, int, int);
	virtual ~Date(void);
};
