#pragma once
#include <string>
#include "Person.hpp"

using namespace std;

class BankClient :	public Person
{
	

public:
	BankClient(void);
	BankClient(string, string, string, string);
	virtual ~BankClient(void);

	virtual string name() const;
	virtual string birthDate() const;
	virtual string address() const;
	virtual string nationality() const;
private:
	string name_;
	string birthdate_;
	string address_;
	string nationality_;
};
