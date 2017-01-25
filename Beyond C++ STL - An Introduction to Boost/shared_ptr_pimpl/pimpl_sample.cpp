
#include "pimpl_sample.hpp"

#include <string>
#include <iostream>

struct impl
{
	void do_something()	{
		std::cout << s_ << std::endl;
	}

	void setvalue(const std::string& s) {
		s_ = s;
	}

	std::string& getvalue() {
		return s_;
	}

	std::string s_;
};

void pimpl_sample::setvalue(const std::string& s) {
	pimpl_->setvalue(s);
}

std::string& pimpl_sample::getvalue() {
	return pimpl_->getvalue();
}

pimpl_sample::pimpl_sample() : pimpl_( new impl() ) {
	pimpl_->s_ = "This is the pimpl idiom, revisited.";
}

pimpl_sample::pimpl_sample(const std::string& s) : pimpl_( new impl() ) {
	pimpl_->s_ = s;
}


//
// By letting a shared_ptr handle the lifetime management of the hidden impl class, 
// and after removing the deletion of the impl from the destructor 
// (it's no longer needed, thanks to shared_ptr), we're done.
//
// However, you must still remember to define the destructor manually;
// the reason is that at the time the compiler generates an implicit destructor, 
// the type impl is incomplete, so its destructor isn't called.
//
pimpl_sample::~pimpl_sample() {
//	delete pimpl_;
}

void pimpl_sample::do_something() {
	pimpl_->do_something();
}
