#include <iostream>
#include "SavingsAccount.hpp"

SavingsAccount::SavingsAccount(const Person *primaryOwner,
								 const Person *jointOwner) : BankAccount(primaryOwner, jointOwner) {
}

SavingsAccount::~SavingsAccount(void) {
}

void SavingsAccount::makeDeposit(double amount) {
}

void SavingsAccount::makeWithdrawal(double amount) {
}

double SavingsAccount::balance() const {
	// just call base (default) implementation
	return BankAccount::balance();
}

void SavingsAccount::creditInterest() {
	//
	// will not call base (default) implementation
	// this is very ChequingAccount specific calculation
	std::cout << "SavingsAccount::creditInterest()" << std::endl;
}
