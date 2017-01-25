#pragma once
#include <string>

// forward declaration
void logCall(const std::string& funcName);	// make a log entry

class Customer
{
public:
	Customer(const std::string& n) : name(n) {
		logCall("Customer constructor, with member initialization");
	}
	Customer(const Customer& rhs) : name(rhs.name) {
		logCall("Customer copy constructor");
	}
	virtual ~Customer(void) {
		logCall("Customer detructor");
	}

	Customer& operator=(const Customer& rhs) {
		logCall("Customer copy assignment operator");
		name = rhs.name;                               // copy rhs's data
		return *this;                                  // see Item 10
	}

	void setName(const std::string newName) {
		name = newName;
	}

private:
	std::string name;
};
