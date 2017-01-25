#pragma once
#include <iostream>

class SimpleBase
{
public:
	SimpleBase(void);
	virtual ~SimpleBase(void);

	int simple_mf(void) {
		using namespace std;
		cout << "SimpleBase::simple_mf()" << endl;
		return 0;
	}

	virtual int virtual_mf(void) {
		using namespace std;
		cout << "SimpleBase::virtual_mf()" << endl;
		return 0;
	}
};
