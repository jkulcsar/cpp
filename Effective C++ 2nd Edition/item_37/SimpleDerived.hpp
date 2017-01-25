#pragma once
#include "SimpleBase.hpp"
#include <iostream>



class SimpleDerived :
	public SimpleBase
{
public:
	SimpleDerived(void);
	virtual ~SimpleDerived(void);

	//
	// redefine the inherited non-virtual function
	int simple_mf(void) { 
		using namespace std;
		cout << "SimpleDerived::simple_mf()" << endl;
		return 0;
	}

	virtual int virtual_mf(void) {
		using namespace std;
		cout << "SimpleDerived::virtual_mf()" << endl;
		return 0;
	}
};
