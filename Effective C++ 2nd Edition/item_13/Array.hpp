#pragma once

#include <vector>


///
/// Class members are initialized in the order of their declaration
/// in the class.
/// The order in which they are listed in the initialization list does
/// not make any difference.
///
/// Here:
/// 'lBound' and 'hBound' is always initialized before 'size';
/// 'size' is always initialised before 'data';
///
template<typename T>
class Array
{
private:
	int lBound, hBound;
	size_t size;
	std::vector<T> data;

public:
	Array(int lowBound, int highBound);
	Array(void);
	~Array(void);
};

///
/// List members in the initialization list
/// in the order in which they are declared;
/// class members are always initialized
/// in the order in which they are declared,
/// not in the order of the initialization list.
///
template<typename T>
Array<T>::Array(int lowBound, int highBound) : 
	lBound(lowBound),
	hBound(highBound),
	size(hBound - lBound + 1),
	data(size)
{
}

template<class T>
Array<T>::Array(void)
{
}

template<class T>
Array<T>::~Array(void)
{
}
