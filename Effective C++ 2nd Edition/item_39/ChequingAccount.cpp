#include <iostream>
#include "ChequingAccount.hpp"

ChequingAccount::ChequingAccount(const Person *primaryOwner,
								 const Person *jointOwner) : BankAccount(primaryOwner, jointOwner) {
}

ChequingAccount::~ChequingAccount(void) {
}

void ChequingAccount::makeDeposit(double amount) {
}

void ChequingAccount::makeWithdrawal(double amount) {
}

double ChequingAccount::balance() const {
	// just call base (default) implementation
	return BankAccount::balance();
}

void ChequingAccount::creditInterest() {
	//
	// will not call base (default) implementation
	// this is very ChequingAccount specific calculation
	std::cout << "ChequingAccount::creditInterest()" << std::endl;
}
