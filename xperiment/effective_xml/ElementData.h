#pragma once
#include "Element.h"
#include <string>
#include <iostream>
#include <sstream>
#include <map>

template<typename T>
class ElementData	:	public Element
{
	T&	ref_;
public:
	ElementData(T& item) : ref_(item) {}
	virtual void put(const std::string& s) const
	{
		std::istringstream	stream(s);
		stream >> ref_;
	}
	const std::string get(void) const
	{
		std::ostringstream	stream;
		stream << ref_;
		
		return stream.str();
	}
};

typedef std::map<const std::string, const Element*> ElementMap_t;
