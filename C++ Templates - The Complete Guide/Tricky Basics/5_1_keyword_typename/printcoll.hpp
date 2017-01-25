//
// 5.1 Keyword typename
// The keyword typename was introduced during the standardization of C++ to clarify 
// that an identifier inside a template is a type. Consider the following example:

template <typename T> 
class MyClass { 
   typename T::SubType * ptr; 
   /// … 
}; 

// Here, the second typename is used to clarify that SubType is a type defined within
// class T. Thus, ptr is a pointer to the type T::SubType.
// Without typename, SubType would be considered a static member. Thus, it would be a 
// concrete variable or object. As a result, the expression
// T::SubType * ptr 
// would be a multiplication of the static SubType member of class T with ptr.

// In general, typename has to be used whenever a name that depends on a template 
// parameter is a type. This is discussed in detail in Section 9.3.2 on page 130.

// A typical application of typename is the access to iterators of STL containers in 
// template code:

// basics/printcoll.hpp 

#include <iostream> 

// print elements of an STL container 
template <typename T> 
void printcoll (T const& coll) 
{ 
    typename T::const_iterator pos;  // iterator to iterate over coll 
    typename T::const_iterator end(coll.end());  // end position 

    for (pos=coll.begin(); pos!=end; ++pos) { 
        std::cout << *pos << ' '; 
    } 
    std::cout << std::endl; 
} 
