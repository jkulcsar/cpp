
#include <string>

template<class T>
class NamedPtr
{
public:

	///
	/// make assignements in constructor body
	///
	NamedPtr( const std::string& initName, T *initPtr )
	{
		std::string name = initName;
		ptr = initPtr;
	}

private:
	std::string name;
	T *ptr;
};
