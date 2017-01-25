
#ifndef EMPTY_HPP
#define EMPTY_HPP

#include <iostream>

namespace br_stl
{

struct Empty
{
public:
	Empty(int = 0) {}
	bool operator<(const Empty&) const { return true; }
};
} // end br_stl namespace

inline std::ostream& operator<<(std::ostream& os, const br_stl::Empty&)
{
	return os;
}

inline std::istream& operator>>(std::istream& is, br_stl::Empty&)
{
	return is;
}


#endif
