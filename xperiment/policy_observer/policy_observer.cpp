
#include <iostream>
#include <vector>

#include "BaseSubject.hpp"
#include "BareBoneSubject.hpp"
#include "ClosedNotify.hpp"

using namespace std;



int main( int argc , char** argv )
{
	cout << "The name of this program is " << argv[0] << endl;
	cout << "This program was invoked with " << argc-1 << " arguments" << endl;

	if( argc > 1 )	{
		cout << "Command line arguments are:" << endl;
		for( int i = 0; i < argc; ++i )
			cout << argv[i] << endl;
	}

	typedef BaseSubject<int> MySubject;
	typedef MySubject::Observer MyObserver;
	typedef ClosedNotify<BareBoneSubject<int> > MySubjectImpl;

	return 0;
}