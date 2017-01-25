
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

#include "pasync.h"
using namespace pt;

#define MAX_INT	100000	// set it as a program argument!

class threadMaster : public thread	{
public:
	threadMaster(trigger& t, vector<char>& coll) :	thread(false), 
													_t(t), 
													_coll( coll)  { 
	};
	
	~threadMaster(){ };

	// master thread needs a job done by slave in sync
	void execute()	{
		for( int i = 0; i < MAX_INT; ++i ){
			cout << "+";
			_coll.push_back('+');
		}
	
		// finished; signal it for main thread
		_t.post();
	}

	void cleanup()	{
	}

private:
	// trigger to signal master thread's job has finished
	trigger&		_t;
	vector<char>&	_coll;
};


class threadSlave : public thread	{
public:
	threadSlave(vector<char>& coll) :	thread(false), _coll(coll)	{
	};
	
	~threadSlave(){};

	void execute()	{
		for( int i = 0; i < MAX_INT; ++i )
			cout << "-";
	}

	void cleanup()	{
	}

private:
	vector<char>&	_coll;
};


int main( int argc , char** argv )
{
	cout << "The name of this program is " << argv[0] << endl;
	cout << "This program was invoked with " << argc-1 << " arguments" << endl;

	if( argc > 1 )	{
		cout << "Command line arguments are:" << endl;
		for( int i = 0; i < argc; ++i )
			cout << argv[i] << endl;
	}

	trigger	triggerFinish(false, false);
	vector<char>	collection;

	auto_ptr< threadMaster > pthreadMaster(new threadMaster(triggerFinish, collection) );
	auto_ptr< threadSlave > pthreadSlave(new threadSlave(collection));
	pthreadMaster->start();
	pthreadSlave->start();

	// wait on this for signal to exit; signaled by master thread
	triggerFinish.wait();

	return 0;
}