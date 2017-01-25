#include "RealPerson.hpp"

Person * Person::makePerson(const string& name,
                            const Date& birthday,
                            const Address& addr,
                            const Country& country)
{
  return new RealPerson(name, birthday, addr, country);
}

//...                      // copy ctor, operator=

std::string RealPerson::name() const {
	return name_;
}

std::string RealPerson::birthDate() const {
	return birthday_.getAsString();
}

std::string RealPerson::address() const {
	return address_.getAsString();
}

std::string RealPerson::nationality() const {
	return country_.getAsString();
}
