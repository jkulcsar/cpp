		
#include <string>
#include "Address.hpp"
#include "Country.hpp"
#include "Date.hpp"

using namespace std;

		////
		//// forward declarations:
		////

		//class string;

		//class Address;
		//class Country;
		//class Date;

class PersonImpl {
public:
  PersonImpl(const string& name, const Date& birthday,
         const Address& addr, const Country& country);
  virtual ~PersonImpl();
  //...                      // copy ctor, operator=
  string name() const;
  string birthDate() const;
  string address() const;
  string nationality() const;

private:
//  member variables should be in the impl class
//  when using the pImpl technique
	string name_;
	Address address_;
	Country nationality_;
	Date birthdate_;

};