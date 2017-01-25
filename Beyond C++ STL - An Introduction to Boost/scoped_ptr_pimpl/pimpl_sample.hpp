
// pimpl_sample.hpp

#if !defined(PIMPL_SAMPLE_HPP)
#define PIMPL_SAMPLE_HPP

#include "boost/scoped_ptr.hpp"

struct impl;

class pimpl_sample
{
	//
	// using raw pointers is not exception safe;
	// if the constructor throws, means that the
	// object never fully existed hence it's 
	// destructor will never be called --> memory leaks
//	impl *pimpl_;
	boost::scoped_ptr<impl> pimpl_;
	
public:
	pimpl_sample();
	~pimpl_sample();
	void do_something();
};

#endif
