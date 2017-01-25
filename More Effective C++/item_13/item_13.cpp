
//
// Item 13: catch exceptions by reference.
//
// For more details see also the Exception Handling project in the walk-through
// code of The C++ Programming Language (Stroustrup).
//


#include <iostream>

//
// class exception is defined in STL
// just re-using the name and inheritance model

class exception {
public:
	virtual const char* what() throw() {
		return "An exception of type 'exception' has been thrown";
	}
	// ...
};

class runtime_error : public exception {
	// ...
};

class Validation_Error : public runtime_error {

public:
	virtual const char* what() throw() {
		return "An exception of type 'Validation_Error' has been thrown";
	}
// ...
};

void someFunction() {
	// ...
	if(1) { // simulate if a validation test fail
		throw Validation_Error();
	}
}

void doSomething_Wrong() {
	try {
		someFunction();		// may throw a validation exception
	}
	catch(exception ex) {
		// calls exception::what(), never Validation_Error::what
		// even if Validation_Error redefines the virtual function,
		// because the exception was caught-by-value, so "slicing" occurs
		// (see the Stroustrup example mentioned above!)
		std::cerr << ex.what() << std::endl;
	}
}

void doSomething_Right() {
	try {
		someFunction();		// may throw a validation exception
	}
	catch(exception& ex) {
		// now calls Validation_Error::what() correctly, not exception::what()
		// no slicing occurs when exceptions are caught by reference
		std::cerr << ex.what();
	}
}

int main(int argc, char** argv) {
	doSomething_Wrong();
	doSomething_Right();

	return 0;
}