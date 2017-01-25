#pragma once
#include <string>

class Airport
{
public:
	Airport(void);
	virtual ~Airport(void);
	Airport(const std::string name) : name_(name) {}
	std::string getName() const { return name_; }
private:
	std::string name_;

protected:

	//
	// making copies of Airport objects doesn't make sense
	// so just declare the copy constructor and
	// assignement operator private (or protected)
	Airport(const Airport&) {}
	Airport& operator=(const Airport&) {}
};
