#pragma once

#include <string>


class Element
{
public:
	virtual void put( const std::string& s ) const = 0;
	virtual const std::string get(void) const = 0;
	virtual ~Element() { }
};
