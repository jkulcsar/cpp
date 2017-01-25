
#include <iostream>
#include <string>

#include "boost/date_time/posix_time/posix_time_types.hpp" //no i/o just types

using namespace boost::posix_time;

int main(int argc, char** argv) {
	

	time_duration td = milliseconds(60814278);

	std::cout << td.total_milliseconds() << std::endl;

	long h = td.hours();
	long m = td.minutes();
	long s = td.seconds();
	long ms = td.fractional_seconds();

	std::cout << h << ":" << m << ":" << s << ":" << ms << std::endl;

	time_duration td_ms_only(0,0,0,ms);
	std::cout << td_ms_only.total_milliseconds() << std::endl;

	time_duration td_rev(h,m,s,ms);

	std::cout << td_rev.total_milliseconds() << std::endl;

	return 0;
}