#include <boost/timer/timer.hpp>
#include <cmath>

#include <iostream>
#include <string>
#include <sstream>


int main()
{
	// boost::timer::auto_cpu_timer t;

	std::ostringstream ostr;
	boost::timer::cpu_timer t_formatted;

	double result = 0;
	t_formatted.start();
	for (long i = 0; i < 10000000; ++i)
		result += std::sqrt(123.456L); // burn some time
	t_formatted.stop();

	ostr << t_formatted.format(3);
	std::cout << "From stringstream: " << ostr.str() << std::endl;
	std::cout << "Calculation result: " << result << std::endl;

	return 0;
}
