#include "BankClient.hpp"

using namespace std;

Person * Person::makePerson(const string& name,
                            const string& birthday,
                            const string& addr,
                            const string& country)
{
  return new BankClient(name, birthday, addr, country);
}

//...                      // copy ctor, operator=

BankClient::BankClient(void){
}

BankClient::BankClient(string name, string birthday, string addr, string country) :
	name_(name), birthdate_(birthday), address_(addr), nationality_(country) {
}

BankClient::~BankClient(void){
}

string BankClient::name() const {
	return name_;
}

string BankClient::birthDate() const {
	return birthdate_;
}

string BankClient::address() const {
	return address_;
}

string BankClient::nationality() const {
	return nationality_;
}
