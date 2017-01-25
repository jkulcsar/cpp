#include <string>

//
//Construction of objects proceeds in two phases: 
//
//(1)Initialization of data members. (See also Item 13.) 
//(2)Execution of the body of the constructor that was called. 
//

template<typename T>
class NamedPtr2
{
public:

	///
	/// use member initialization list
	///
	NamedPtr2( const std::string& initName, T *initPtr ) : name(initName), ptr(initPtr)
	{
	}

	///
	/// item 16
	/// assignement operator must assign ALL member variables
	NamedPtr2& operator=(const NamedPtr2& rhs);
private:
	std::string name;
	T *ptr;
};

template<typename T>
NamedPtr2<T>& NamedPtr2<T>::operator =(const NamedPtr2<T> &rhs)
{
	///
	/// check for self-assignement (item 17)
	if(this == &rhs)
		return *this;

	/// assign to all data members
	name = rhs.name;

	/// for a pointer, assign what's pointed to,
	/// not the pointer itself!
	*ptr = *rhs.ptr;

	return *this;	// item 15
}