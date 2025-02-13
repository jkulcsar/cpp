
//
// item_43: prefer algorithm calls to hand written loops

#include <algorithm>
#include <iostream>
#include <list>
#include <functional>

class Widget
{
public:
	void redraw()
	{
		std::cout << "redrawing" << std::endl;
	}
};

int main(int argc, char** argv)
{
	std::list<Widget> lw;
	lw.push_back(Widget());
	lw.push_back(Widget());
	lw.push_back(Widget());

	std::for_each( lw.begin(), lw.end(), std::mem_fun_ref(&Widget::redraw) );

	return 0;
}
