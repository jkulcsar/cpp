
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <cassert>
#include <map>
#include <string>

class A {
	boost::shared_ptr<int> no_;
public:
	A(boost::shared_ptr<int> no) : no_(no) {}
	void setvalue(int i) {
		*no_ = i;
	}
};

class B {
	boost::shared_ptr<int> no_;
public:
	B(boost::shared_ptr<int> no) : no_(no) {}
	int getvalue() const {
		return *no_;
	}
};

class Simple : public boost::enable_shared_from_this<Simple> {
	int	i_;
	std::string s_;
public:
	Simple( int i, const std::string& s ) : i_(i), s_(s) {
	}
};

typedef boost::shared_ptr<Simple> Simple_ptr;
typedef std::map<char, Simple_ptr> map_of_Simples;

int main(int argc, char** argv)
{
	boost::shared_ptr<int> temp(new int(14));

	A a(temp);
	B b(temp);
	a.setvalue(28);
	assert(b.getvalue() == 28);

	// create a map of shared_ptrs
	map_of_Simples simples;
	Simple_ptr s1(new Simple(11, "Seven11"));
	Simple_ptr s2(s1);
	simples.insert(std::make_pair('A', s1));
	simples.insert(std::make_pair('B', s2));

	map_of_Simples more_simples;
	map_of_Simples::const_iterator citer;

	citer = more_simples.find('A');
	if(citer != more_simples.end()) {
		const Simple_ptr& sptr = citer->second;
	}

	return 0;
}