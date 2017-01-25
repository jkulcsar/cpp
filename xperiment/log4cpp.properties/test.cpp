// test.cpp : Defines the entry point for the console application.
//

#include <fstream>
#include <iostream>
#include <string>

#include "log4cpp/Properties.hh"

static log4cpp::Properties properties;

std::string bar (const std::string& k, const std::string& v)
{
	std::string s = properties.getString (k, v.c_str());
	return s;

}
int main(int argc, char *argv[])
{
        std::cout << "starting..." << std::endl;
	std::string fname = "log4cpp.properties";
	std::ifstream in(fname.c_str());
	properties.load (in);

	std::string k = "appender.A1";
	std::string v = "someappender";
	std::string s = bar(k, v);
        std::cout << "key=" << s << std::endl;

	return 0;
}

