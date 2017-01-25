#pragma once
#include "BankAccount.hpp"

class SavingsAccount :
	public BankAccount
{
public:
	SavingsAccount(const Person *primaryOwner, const Person *jointOwner);
	virtual ~SavingsAccount(void);
	virtual void makeDeposit(double amount);
	virtual void makeWithdrawal(double amount);
	virtual double balance() const;
	virtual void creditInterest();
};
