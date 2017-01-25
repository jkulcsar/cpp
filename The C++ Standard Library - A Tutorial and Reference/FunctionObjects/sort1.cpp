
#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;


class Person {
public:
	Person(string f, string l) : firstname_(f), lastname_(l) {
	}
	string firstname() const {
		return firstname_;
	}
	string lastname() const {
		return lastname_;
	}

	bool operator < (Person const& rhs) const {
		if( lastname_ < rhs.lastname())
			return true;
		else
			return false;
	}

	bool operator > (Person const& rhs) const {
		if( lastname_ > rhs.lastname())
			return true;
		else
			return false;
	}

private:
	string firstname_;
	string lastname_;
};

// class for function predicate
// operator() returns whether a person is less than another
//

class PersonSortCriterion {
public:
	bool operator() (const Person& p1, const Person& p2) const {
		// a person is less than another if:
		// (1) if the last name is less
		// (2) if the last name is equal and the first name is less
		return p1.lastname() < p2.lastname() || 
			(! (p2.lastname() < p1.lastname()) && p1.firstname() < p2.firstname());
	}
};

int main(int argc, char** argv) {

	// sort with standard operator < 
	typedef std::set<Person, std::less<Person> > AscendingPersonSet;
	AscendingPersonSet personsSortedAscending;

	// sort with standard operator >
	typedef std::set<Person, std::greater<Person> > DescendingPersonSet;
	DescendingPersonSet personsSortedDescending;

	// sort with our functor (PersonSortCriterion)
	typedef set<Person, PersonSortCriterion> PersonSet;
	PersonSet people;

	people.insert(Person("Elvis", "Presley"));
	people.insert(Person("Abraham", "Lincoln"));
	people.insert(Person("Amelia", "Earhart"));

	{
		// show the collection
		std::cout << "Sorted, using custom sort criterion:" << std::endl;
		PersonSet::iterator pos;
		for(pos = people.begin(); pos != people.end(); ++pos) {
			cout << pos->lastname() << ", " << pos->firstname() << endl;
		}
	}


	personsSortedAscending.insert(Person("Elvis", "Presley"));
	personsSortedAscending.insert(Person("Abraham", "Lincoln"));
	personsSortedAscending.insert(Person("Amelia", "Earhart"));

	{
		// show the collection
		std::cout << "Sorted, using standard operator less<> :" << std::endl;
		AscendingPersonSet::iterator pos;
		for(pos = personsSortedAscending.begin(); pos != personsSortedAscending.end(); ++pos) {
			cout << pos->lastname() << ", " << pos->firstname() << endl;
		}
	}

	personsSortedDescending.insert(Person("Elvis", "Presley"));
	personsSortedDescending.insert(Person("Abraham", "Lincoln"));
	personsSortedDescending.insert(Person("Amelia", "Earhart"));

	{
		// show the collection
		std::cout << "Sorted, using standard operator greater<> :" << std::endl;
		DescendingPersonSet::iterator pos;
		for(pos = personsSortedDescending.begin(); pos != personsSortedDescending.end(); ++pos) {
			cout << pos->lastname() << ", " << pos->firstname() << endl;
		}
	}

}