
#include "StandardNewDeleteForms.hpp"

class Widget: public StandardNewDeleteForms {           // inherit std forms

public:

   using StandardNewDeleteForms::operator new;          // make those
   using StandardNewDeleteForms::operator delete;       // forms visible



   static void* operator new(std::size_t size,          // add a custom
                             std::ostream& logStream)   // placement new
     throw(std::bad_alloc)
   {
	   logStream << "allocating" << std::endl;
	   return ::operator new(size);
   }



   static void operator delete(void *pMemory,           // add the corres-
                               std::ostream& logStream) // ponding place-
    throw()                                            // ment delete
   {
		//  ...
	   logStream << "deleting" << std::endl;
   }

};
