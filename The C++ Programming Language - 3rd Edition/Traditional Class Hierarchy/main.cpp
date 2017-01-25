#include <iostream>
#include <memory>

#include "Ival_box.h"
#include "Ival_slider.h"
#include "Ival_dial.h"

void interact(Ival_box* pb)
{
	pb->prompt();
	// ...
	int i = pb->get_value();
	if( pb->was_changed() )
	{
		// new value; do something...
	}
	else
	{
		// old value was fine; do something else...
	}
	// ...
}

void some_fct()
{
	std::auto_ptr<Ival_slider> p1(new Ival_slider(0,5));
	interact(p1.get());

	std::auto_ptr<Ival_box> p2(new Ival_dial(1,12));
	interact(p2.get());

	//Ival_box* p1 = new Ival_slider(0,5);
	//interact(p1);

	//Ival_box* p2 = new Ival_dial(1,12);
	//interact(p2);

	//if(p1)
	//{
	//	delete p1; p1 = NULL;
	//}
	//if(p2)
	//{
	//	delete p2; p2 = NULL;
	//}

}

int main( int argc , char** argv )
{
	std::cout << "The name of this program is " << argv[0] << std::endl;
	std::cout << "This program was invoked with " << argc-1 << " arguments" << std::endl;

	if( argc > 1 )	{
		std::cout << "Command line arguments are:" << std::endl;
		for( int i = 0; i < argc; ++i )
			std::cout << argv[i] << std::endl;
	}

	some_fct();

	return 0;
}