			////
			//// forward declarations:
			////

			//class string;

			//class Address;
			//class Country;
			//class Date;

			//// declaration of the class that will contain
			//// the implementation details for Person object;
			//// this is just a forward declaration
			////
			//// note that the pimpl class must have -exactly- the
			//// same member functions as Person (the 'owner' class);
			//// the share the same interface 
			//class PersonImpl;

			//class PersonWithPImpl {
			//public:
			//  PersonWithPImpl(const string& name, const Date& birthday,
			//		 const Address& addr, const Country& country);
			//  virtual ~PersonWithPImpl();
			//  //...                      // copy ctor, operator=
			//  string name() const;
			//  string birthDate() const;
			//  string address() const;
			//  string nationality() const;

			//private:
			////  member variables should be in the impl class
			////  when using the pImpl technique
			////	string name_;
			////	Address address_;
			////	Country nationality_;
			////	Date birthdate_;

			//	PersonImpl	*pImpl_;
			//};

#include <string>
using namespace std;

class Date;
class Address;
class Country;

class Person {
public:
	virtual ~Person() {}
  
	virtual string name() const = 0;
	virtual string birthDate() const = 0;
	virtual string address() const = 0;
	virtual string nationality() const = 0;

	// makePerson is now a member of the class
	static Person * makePerson(const string& name,
                             const Date& birthday,
                             const Address& addr,
                             const Country& country);
};
