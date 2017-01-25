
#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include "boost/any.hpp"


struct streamer {
	virtual void print(std::ostream& o, boost::any& a) = 0;
	virtual streamer* clone() = 0;
	virtual ~streamer() {};
};

template<typename T>
struct streamer_impl : public streamer {
	virtual void print(std::ostream& o, boost::any& a) {
		o << boost::any_cast<T>(a);
	}

	virtual streamer* clone() {
		return new streamer_impl<T>();
	}
};

class any_out {
	boost::any o_;
	streamer* streamer_;
public:
	// default constructor
	any_out() : streamer_(0) {
	}

	// parameterized constructor
	template<typename T>
	any_out(const T& value) : streamer_(new streamer_impl<T>), o_(value) {
	}

	// copy constructor
	// (make sure that streamer in source any_out is not null)
	any_out(const any_out& a) : streamer_( a.streamer_ ? a.streamer_->clone() : 0 ), o_(a.o_) {
	}

	// assignement operator
	any_out& operator=(const any_out& r) {
	  any_out(r).swap(*this);
	  return *this;
	}

	// the swap function is supplied to facilitate exception-safe assignment
	any_out& swap(any_out& r) {
	  std::swap(streamer_, r.streamer_);
	  std::swap(o_,r.o_);
	  return *this;
	}

	// dtor
	~any_out() {
	  delete streamer_;
	}

	// the output operator
	friend std::ostream& operator<< (std::ostream& o, any_out& a) {
		if(a.streamer_) {
			a.streamer_->print(o, a.o_);
		}
		return o;
	}
};


int main(int argc, char** argv) {
	std::vector<any_out> vec;

	any_out a(std::string("I do have operator<< !"));

	vec.push_back(a);
	vec.push_back(112);
	vec.push_back(65.545);

	//std::copy(vec.begin(), vec.end(), 
	//	std::ostream_iterator<any_out>(std::cout, " "));

	std::cout << vec[0] << std::endl;
	std::cout << vec[1] << std::endl;
	std::cout << vec[2] << std::endl;

	a = std::string("This is great!");
	std::cout << a << std::endl;

	return 0;
}