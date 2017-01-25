
#ifndef HMAP_HPP__
#define HMAP_HPP__

#include <vector>
#include <list>

#include <cassert>
#include <algorithm>

namespace stl_applications
{

template<typename Key, typename T, typename hashFun>
class hmap
{
public:
	typedef size_t size_type;
	typedef std::pair<const Key, T> value_type;

	// define simplified denominations
	typedef std::list<value_type> list_type;
	typedef std::vector<list_type*> vector_type;

	//The template parameter Key stands for the type of the key; T stands for the class
	//of data associated to a key; and hashFun is the placeholder for the data type
	//of the function objects used for address calculation. Below, a function object for
	//address calculation is proposed, but any other one can be used as well. Analogous
	//to map, value_type is the type of the elements that are stored in a HMap object.
	//value_type is a pair consisting of a constant key and the associated data.
	
	class iterator;
	typedef iterator const_iterator; // maintain STL compatibility
	friend class iterator;
	//The nested class iterator cooperates closely with HMap, so that both are mutually
	//declared as friend. iterator is only supposed to allow forward traversal
	//and therefore its category is of the standard type forward_iterator_tag.
	//An iterator object allows you to visit all the elements of a HMap object one after the
	//other. Neither an order nor a sorting is defined for the elements. The visiting order
	//of the iterator is given by the implicit data structure (see below, operator++()).

	class iterator
	{
		friend class HMap<Key, T, hashFun>;

	};
	


};

} // end namespace stl_applications

#endif