
#include <iostream>
#include <memory>
#include "Customer.hpp"
#include "PriorityCustomer.hpp"

void logCall(const std::string& funcName) {
	std::cout << funcName << std::endl;
}
int main(int argc, char** argv) {
	Customer c1("Mark Twain");
	Customer c2(c1);	// call copy ctor
	Customer c3 = c1;	// also calls copy ctor!

	std::cout << std::endl;

	PriorityCustomer important1("Huck Finn", 1);
	PriorityCustomer important2(important1);	// call copy ctor
	important2.setName("Tom Sawyer");

	std::cout << std::endl;

	std::shared_ptr<Customer> shpCustomer( new Customer("Smart Customer") );
	std::shared_ptr<PriorityCustomer> shpPCustomer;
	
	return 0;
}