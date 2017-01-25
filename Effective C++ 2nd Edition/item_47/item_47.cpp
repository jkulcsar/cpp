
//
// Item 47:
// Ensure that non-local static objects are initialized before they're used.
//
// This is an extended study on static objects; includes a lot from the Stroustrup C++ book


#include <iostream>

#include "FileSystem.hpp"
#include "Directory.hpp"

#include "Date.hpp"

//A variable that is part of a class, yet is not part of an object of that class, is called a
//static member. There is exactly one copy of a static member instead of one copy per object, as for
//ordinary nonstatic members. Similarly, a function that needs access to members of a class, yet
//doesn’t need to be invoked for a particular object, is called a static member function.

//static
//	anachronism 200
//	deprecated 818
//	local 145
//	member 228, 421
//	member function 278
//	member of template 854
//	object 244
//	store, local 251
//
//In C and older C++ programs, the keyword s t a t i c is (confusingly) used to mean ‘‘use internal
//linkage’’ (§B.2.3). Don’t use s t a t i c except inside functions (§7.1.2) and classes (§10.2.4).


//
// Non-local static objects are objects that:
// (1) defined at global namespace scope (here: theFileSystem, tempDir)
// (2) declared static in a class
// (3) defined static at a file scope

// ???
// ??? difference between static functions and static objects
// ??? must clarify the difference with exact example

// ???
// related question: the bad_ptr situation with pubsub_cxx built with VS2005:
// is it a static initialization (or the lack thereof) issue?

//A local variable is initialized when the thread of execution reaches its definition. By default, this
//happens in every call of the function and each invocation of the function has its own copy of the
//variable. If a local variable is declared s t a t i c , a single, statically allocated object will be used to
//represent that variable in all calls of the function. It will be initialized only the first time the thread
//of execution reaches its definition. For example:

void f(int a)
{
	while (a ) {
		using namespace std;
		static int n = 0; // initialized once
		int x = 0; // initialized n times
		cout << "n == " << n++ 
			<< ", x == " << x++ 
			<< ", a == " << a-- 
			<< endl;
	}
}

Date Date::default_date(16,12,1770);

int main( int argc, char** argv) {
	f(3) ;


}