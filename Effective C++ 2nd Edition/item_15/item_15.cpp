#include "Widget.hpp"


int main( int argc, char* argv[] )
{
	Widget w1, w2;
	w2 = w1;

	Widget wPi(3, 3.14);
	Widget wEu(2, 2.71);
	Widget w;

	w = wPi;
	w = wEu;

	return 0;
}