
//
// class Empty{};
// it's the same as if you'd written this:
//

class Empty {
public:
	Empty() {}                        // default constructor
	Empty(const Empty& rhs) {}        // copy constructor
	~Empty() {}                       // destructor — see
                                      // below for whether
                                      // it's virtual
	Empty&  operator=(const Empty& rhs) { return *this; }    // assignment operator
	Empty* operator&() { return this; }       // address-of operators
	const Empty* operator&() const {return this; }
};

int main(int argc, char** argv)
{
	const Empty e1; // default constructor
	                // also calls default destructor on leaving scope

	Empty e2(e1);	// copy constructor

	e2 = e1;		// assignement operator

	Empty *pe2 = &e2;			// address-of operator (non-const)
	const Empty *pe1 = &e1;		// address-of operator (const)

	return 0;
}