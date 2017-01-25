// include/checkvec.h : vector class with checked limits
#ifndef CHECKVEC_H
#define CHECKVEC_H
#include<cassert>
#include<vector>
// The goal here is simple: write a vector that is automatically index checked.
//
// For this is enough to derive from std::vector and redefine the index operator.
//
//Note: The STL allows inheritance, but does not support polymorphism! In this
//sense, methods of derived classes may be called, but not via pointers or references of
//the base tip class type. In the case of vectors, this is certainly no problem, but be aware
//of it.

namespace br_stl {
	template<class T>
	class checkedVector : public std::vector<T> { // inherit
	public:
		// inherited types
		typedef typename checkedVector::size_type size_type;
		typedef typename checkedVector::iterator iterator;
		typedef typename checkedVector::difference_type difference_type;
		typedef typename checkedVector::reference reference;
		typedef typename checkedVector::const_reference const_reference;

		checkedVector() {
		}
		
		checkedVector(size_type n, const T& value = T())
			: std::vector<T>(n, value) {
		}
		
		checkedVector(iterator i, iterator j)
			: std::vector<T>(i, j) {
		}
		
		reference operator[](difference_type index) {
			assert(index >=0
				&& index < static_cast<difference_type>(size()));
			return std::vector<T>::operator[](index);
		}
		
		const_reference operator[](difference_type index) const {
			assert(index >=0
				&& index < static_cast<difference_type>(size()));
			return std::vector<T>::operator[](index);
		}
	};
}
#endif
