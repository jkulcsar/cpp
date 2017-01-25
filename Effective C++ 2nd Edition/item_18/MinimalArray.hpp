#pragma once

/// Consider a concrete example:
/// a template for classes that implement arrays
/// with client-defined upper and lower bounds
/// and that offer optional bounds-checking

#include <vector>

template<typename T>
class MinimalArray
{
public:
	enum BoundsCheckingStatus
	{
		NO_BOUNDS_CHECK = 0,
		CHECK_BOUNDS = 1
	};

	MinimalArray(int lowBound, int highBound, BoundsCheckingStatus check = NO_BOUNDS_CHECK);
	MinimalArray(const MinimalArray& rhs);
	~MinimalArray();
	MinimalArray& operator=(const MinimalArray& rhs);

	/// return element for read/write
	T& operator[](int index);

	/// return element for read-only
	const T& operator[](int index) const;

	int lowBound() const;
	int highBound() const;

private:
	int lBound, hBound;
	size_t size;
	std::vector<T> data;
	BoundsCheckingStatus checkingBounds;
};

template<typename T>
MinimalArray<T>::MinimalArray(int lowBound, int highBound, BoundsCheckingStatus check = NO_BOUNDS_CHECK) : 
	lBound(lowBound),
	hBound(highBound),
	size(hBound - lBound + 1),
	data(size),
	checkingBounds(check)
{
}

template<class T>
MinimalArray<T>::MinimalArray(const MinimalArray& rhs)
{
}

template<class T>
MinimalArray<T>::~MinimalArray(void)
{
}

template<typename T>
MinimalArray<T>& MinimalArray<T>::operator =(const MinimalArray<T> &rhs)
{
	///
	/// check for self-assignement (item 17)
	if(this == &rhs)
		return *this;

	/// assign to all data members
	lBound = rhs.lBound;
	hBound = rhs.hBound;
	data = rhs.data;	// vector support assignement!
	checkingBounds = rhs.checkingBounds;

	return *this;	// item 15
}

template<typename T>
int MinimalArray<T>::lowBound() const
{
	return lBound;
}

template<typename T> 
int MinimalArray<T>::highBound() const
{
	return hBound;
}

template<typename T>
T& MinimalArray<T>::operator [](int index)
{
	// incorrect and incomplete
	//if(checkingBounds)
	//{
	//	if(index < size)
	//		return data[index];
	//}
	//else
	//	return data[index];

	return data[index-lBound];
}

template<typename T>
const T& MinimalArray<T>::operator [](int index) const
{
	// incorrect and incomplete
	//if(checkingBounds)
	//{
	//	if(index < size)
	//		return data[index] const;
	//}
	//else
	//	return data[index] const;

	return data[index-lBound];
}