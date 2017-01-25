
#pragma once

#include "Uncopyable.hpp"

class HomeForSale {
private:
	// ... other private members here
	HomeForSale(const HomeForSale&);	// declarations only
	HomeForSale& operator=(const HomeForSale&);
public:
	HomeForSale() {}
};

// please note that inheritance need not be public in this case
class HomeForSale2 : private Uncopyable {
	// class no longer declares copy ctor and assignement operator
};
