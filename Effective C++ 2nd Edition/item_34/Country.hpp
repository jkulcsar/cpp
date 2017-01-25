#pragma once

#include <string>
class Country
{
public:
	Country(void);
	Country(std::string&);
	virtual ~Country(void);
	std::string getAsString() const { return country_; }
private:
	std::string country_;
};
