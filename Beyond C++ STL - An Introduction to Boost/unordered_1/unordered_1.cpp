
#include <boost\unordered_set.hpp>
#include <boost\unordered_map.hpp>
#include <iostream>
#include <string>

//
// user defined types must implement hash_value() and operator==()
// for comparison of this type
class person
{
public:
	person( std::string n, int a ) :  name_(n), age_(a)
	{
	}

	bool operator==(const person& p) const
	{
		return name_ == p.name_ && age_ == p.age_;
	}

	std::size_t hash_value( person const& p) const
	{
		std::size_t seed = 0;
		boost::hash_combine( seed, p.name_ );
		boost::hash_combine( seed, p.age_ );
		return seed;
	}

	std::ostream& put(std::ostream& s) const
	{
		s << "\tname:\t" << name_ ;
		s << "\tage:\t" << age_;
		return s;
	}

private:
	std::string name_;
	int age_;
};

//
// must define a hash_value function for the user-define type
// just call the inner hash_value to enable access
// to private data members
std::size_t hash_value( person const& p)
{
	return p.hash_value(p);
}

//
// define the output operator for the user defined type
// just call the public formatter function, here: put
// this enables protection of private data members
// and avoids using friend functions
std::ostream& operator<<( std::ostream& s, const person& p )
{
	return p.put(s);
}

int main( int argc, char** argv )
{
	//
	// simple use of unordered_set
	typedef boost::unordered_set<std::string> unordered_string_set;

	unordered_string_set uss;
	
	uss.insert("Apollo");
	uss.insert("Four");
	uss.insert("Forty");

	for( unordered_string_set::const_iterator citer = uss.begin();
		citer != uss.end();
		++citer)
	{
		std::cout << *citer << std::endl;
	}

	//
	// simple use of unordered_map
	typedef boost::unordered_map<std::string, size_t> unordered_NameAge;

	unordered_NameAge una;
	
	una.insert( unordered_NameAge::value_type("Apollo", 33) );
	una.insert( unordered_NameAge::value_type("Four", 22) );
	una.insert( unordered_NameAge::value_type("Forty", 11) );

	for( unordered_NameAge::const_iterator citer = una.begin();
		citer != una.end();
		++citer)
	{
		std::cout << citer->first << "|" << citer->second << std::endl;
	}

	//
	// using a user defined type with unordered_*
	typedef boost::unordered_set<person> people_set_type;

	people_set_type people;

	people.insert( person("Boris", 33) );
	people.insert( person("Henry", 8) );
	people.insert( person("Apollo", 440) );

	for( people_set_type::const_iterator citer = people.begin();
		citer != people.end();
		++citer)
	{
		std::cout << *citer << std::endl;
	}

	//
	// now, lets' build a map of persons-to-wages
	typedef boost::unordered_map<person, long> people_map_type;
	people_map_type salaries;

	salaries.insert( std::make_pair( person("Fred",  43), 98000 ) );
	salaries.insert( std::make_pair( person("Boris", 33), 99000 ) );
	salaries.insert( std::make_pair( person("Henry", 22), 89000 ) );
	salaries.insert( std::make_pair( person("M",  40), 98000 ) );


	people_map_type::const_iterator cit = salaries.begin();
	while( cit != salaries.end() )
	{
		std::cout << cit->first << "|" << cit->second << std::endl;
		++cit;
	}
	std::cout << std::endl;



	return 0;
}
