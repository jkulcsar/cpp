
#include <iostream>
#include <string>
#include "boost/tuple/tuple.hpp"

int main() {
	boost::tuple<int, double, std::string>
		triple(42, 3.14, "The amazing tuple!");

	int i = boost::tuples::get<0>(triple);
	double d = triple.get<1>();
	std::string s = boost::get<2>(triple);

	return 0;
}