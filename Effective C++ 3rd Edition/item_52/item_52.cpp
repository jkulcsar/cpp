
//
// item 52: write placement delete if you write placement new

#include <iostream>

#include "Widget.hpp"

int main(int argc, char** argv)
{

	Widget* pw1 = new Widget;
	delete pw1;

	Widget* pw2 = new (std::cerr) Widget;
//	delete pw2 (std::cerr);

	Widget* pw3 = new (std::nothrow) Widget;
	if( pw3 == 0 )
	{
		//... test may succeed
	}

	delete pw3;

/*
Is there a "placement delete"?
---------------------------------

No, but if you need one you can write your own.
Consider placement new used to place objects in a set of arenas

        class Arena {
        public:
                void* allocate(size_t);
                void deallocate(void*);
                // ...
        };

        void* operator new(size_t sz, Arena& a)
        {
                return a.allocate(sz);
        }

        Arena a1(some arguments);
        Arena a2(some arguments);
Given that, we can write
        X* p1 = new(a1) X;
        Y* p2 = new(a1) Y;
        Z* p3 = new(a2) Z;
        // ...
But how can we later delete those objects correctly? The reason that there is no 
built-in "placement delete" to match placement new is that there is no 
general way of assuring that it would be used correctly. 
Nothing in the C++ type system allows us to deduce that p1 points to an object 
allocated in Arena a1. A pointer to any X allocated anywhere can be assigned to p1.
However, sometimes the programmer does know, and there is a way:

        template<class T> void destroy(T* p, Arena& a)
        {
                if (p) {
                        p->~T();		// explicit destructor call
                        a.deallocate(p);
                }
        }
Now, we can write:
        destroy(p1,a1);
        destroy(p2,a2);
        destroy(p3,a3);
If an Arena keeps track of what objects it holds, you can even write destroy() 
to defend itself against mistakes.
It is also possible to define a matching operator new() and operator delete()
pairs for a class hierarchy TC++PL(SE) 15.6. See also D&E 10.4 and TC++PL(SE) 19.4.5.

*/
	return 0;
}
