
#ifndef IOTA_HPP
#define IOTA_HPP

namespace br_stl
{
	template<class ForwardIterator, class T>
	void iota(ForwardIterator first, ForwardIterator last, T value)
	{
		while( first != last )
			*first++ = value++;
	}
} // end namespace br_stl

#endif
