#pragma once

//
// forward declarations
class Person;

class BankAccount {
public:
  BankAccount(const Person *primaryOwner,
	  const Person *jointOwner) : primaryOwner_(primaryOwner), jointOwner_(jointOwner) {
  }
  virtual ~BankAccount() {}
  virtual void makeDeposit(double amount) = 0;
  virtual void makeWithdrawal(double amount) = 0;
  virtual double balance() const = 0 {
	  return balance_;
  }
  virtual void creditInterest() = 0 {
	  //
	  // provide a simple, default implementation
	  // in this case: as a no-op
  }

  const Person* getPrimaryOwner() const {
	  return primaryOwner_;
  }

//  ...

private:
	const Person* primaryOwner_;
	const Person* jointOwner_;
	double balance_;
};
