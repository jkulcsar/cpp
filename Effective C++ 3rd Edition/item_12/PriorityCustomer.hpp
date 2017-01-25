#pragma once
#include "Customer.hpp"

class PriorityCustomer : public Customer
{
public:
	PriorityCustomer(const std::string& n, const int p) : Customer(n), priority(p) {
		logCall("PriorityCustomer constructor, with base class call and member init");
	}
	PriorityCustomer(const PriorityCustomer& rhs) : Customer(rhs), priority(rhs.priority) {
		logCall("PriorityCustomer copy constructor");
	}
	virtual ~PriorityCustomer(void) {
		logCall("PriorityCustomer destructor");
	}

	PriorityCustomer& operator=(const PriorityCustomer& rhs) {
		logCall("PriorityCustomer copy assignment operator");
		Customer::operator =(rhs);
		priority = rhs.priority;
		return *this;
	}

	void setPriority( int newPriority) {
		priority = newPriority;
	}

private:
	int priority;
};
