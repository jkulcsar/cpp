

//
// item_47: consider function objects as algorithm parameters
// instead of functions (or member functions)

#include "..\ESTLUtil_rewrite.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

class Widget
{
	double md;
public:
	Widget(double d) : md(d) {}
	void redraw()
	{
		std::cout << "redrawing" << std::endl;
	}

	bool operator>(const Widget& rhs) const
	{
		if( md > rhs.md )
			return true;
		else
			return false;
	}

	double get_value()
	{
		return md;
	}

	std::ostream& put(const Widget& w, std::ostream& ostr) const
	{
		ostr << md << "|";
		return ostr;
	}
};

std::ostream& operator<<(std::ostream& ostr, const Widget& w)
{
	return w.put(w,ostr);
}

//bool operator>(Widget& lhs, Widget& rhs)
//{
//	if( lhs.get_value() > rhs.get_value() )
//		return true;
//}

int main(int argc, char** argv)
{
	std::vector<Widget> lw;
	lw.push_back(Widget(2.11));
	lw.push_back(Widget(3.14));
	lw.push_back(Widget(2.71));

	printContainer(lw);
	std::sort( lw.begin(), lw.end(), std::greater<Widget>());
	printContainer(lw);

	return 0;
}
