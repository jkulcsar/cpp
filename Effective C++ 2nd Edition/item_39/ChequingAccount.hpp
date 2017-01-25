#pragma once
#include "BankAccount.hpp"

class ChequingAccount :
	public BankAccount
{
public:
	ChequingAccount(const Person *primaryOwner,
              const Person *jointOwner);
	virtual ~ChequingAccount(void);
	virtual void makeDeposit(double amount);
	virtual void makeWithdrawal(double amount);
	virtual double balance() const;
	virtual void creditInterest();
};
