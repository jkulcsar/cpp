
#include <boost\regex.hpp>
#include <locale>
#include <iostream>

int main( int argc, char** argv )
{
	std::locale::global( std::locale("German") );
	std::string name = "Boris Schüßler";
	boost::regex expr("\\w+\\s\\w+");

	// compare string to regex;
	// regex_match() returns true only if entire string matches 
	std::cout << boost::regex_match( name, expr ) << std::endl;

	boost::regex another_expr("(\\w+)\\s(\\w+)");
	boost::smatch what;
	if( boost::regex_search(name, what, expr) )
	{
		std::cout << what[0] << std::endl;
		std::cout << what[1] << "|" << what[2] << std::endl;
	}

	return 0;
}
