#include <list>
#include <iostream>

#include "BankClient.hpp"
#include "ChequingAccount.hpp"
#include "SavingsAccount.hpp"

//
// item 39: Avoid cast-down the inheritance hierarchy
//
// the example implemented here illustrates only the best case
// scenario, avoiding casting all together and relying on the
// dynamic binding of virtual functions;
// does not implement any of the work-around solutions
// discussed in the book
//

int main(int argc, char** argv) {
	BankClient *pElvis = new BankClient(
		"Elvis Presley", 
		"January 8, 1935", 
		"Memphis, TN",
		"USA");

	BankClient *pJohn = new BankClient(
		"John Doe", 
		"January 1, 1959", 
		"New York, NY",
		"USA");

	std::list<BankAccount*> bankAccounts;

	ChequingAccount	ca(pElvis, pJohn);
	SavingsAccount	sa(pJohn, pElvis);

	bankAccounts.push_back(&ca);
	bankAccounts.push_back(&sa);

	std::list<BankAccount*>::iterator pos;
	for(pos = bankAccounts.begin(); pos != bankAccounts.end(); ++pos ) {
		std::cout << (*pos)->getPrimaryOwner()->name() << std::endl;
		(*pos)->creditInterest();
	}

	if(pElvis && pJohn) {
		delete pElvis;
		delete pJohn;
	}

	return 0;
}