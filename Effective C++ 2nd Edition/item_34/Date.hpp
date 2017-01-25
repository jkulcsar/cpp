#pragma once
#include <string>

class Date
{
public:
	Date(void);
	Date(std::string&);
	virtual ~Date(void);
	std::string getAsString() const { return date_; }
private:
	std::string date_;
};
