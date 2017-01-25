#include "Person.hpp"
//#include "PersonImpl.hpp"
//#include "RealPerson.hpp"
#include "Date.hpp"
#include "Address.hpp"
#include "Country.hpp"

#include <iostream>

int main(int argc, char** argv) {

	std::string name = "Elvis";
	
	std::string d = "January 8, 1935";
	Date birthDate(d);

	std::string c = "USA";
	Country country(c);

	std::string a = "Memphis, TN";
	Address address(a);

	Person *elvis = Person::makePerson(name, birthDate, address, country);
	if(elvis) {
		std::cout << elvis->name() << std::endl;
		std::cout << elvis->birthDate() << std::endl;
		std::cout << elvis->address() << std::endl;
		std::cout << elvis->nationality() << std::endl;
		delete elvis;
	}

}