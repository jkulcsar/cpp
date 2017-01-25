#pragma once
#include <string>

class Address
{
public:
	Address(void);
	Address(const std::string&);
	virtual ~Address(void);
	std::string getAsString() const { return address_; }
private:
	std::string address_;
};
