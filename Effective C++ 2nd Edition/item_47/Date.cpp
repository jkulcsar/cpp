#include "Date.hpp"

Date::Date(int dd, int mm, int yy)
{
	d = dd ? dd : default_date.d;
	m = mm ? mm : default_date.m;
	y = yy ? yy : default_date.y;
}
void Date::set_default(int d, int, m, int y) {
	Date::default_date = Date(d,m,y);
}

Date::~Date(void)
{
}
