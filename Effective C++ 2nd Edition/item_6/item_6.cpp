
//
// deleting a null pointer is always safe (it does nothing).
// Thus, if you write your constructors, your assignment operators, 
// and your other member functions such that each pointer member of 
// the class is always either pointing to valid memory or is null, 
// you can merrily delete away in the destructor without regard for 
// whether you ever used new for the pointer in question

class CWithPointer {
	void* p_;
public:
	// ctor
	CWithPointer() : p_(0) {}

	// copy ctor
	CWithPointer(const CWithPointer& rhs) : p_(rhs.p_) {}

	// assignement operator
	CWithPointer& operator=(const CWithPointer& rhs) {
		// check for self-assignement
		if(this == &rhs) {
			return *this;
		}
		
		// no deep copy here;
		// always should for pointers!
		p_ = rhs.p_;
	}

	~CWithPointer() {
		delete p_;
	}

	// address-of operators
	//	CWithPointer* operator&();
	//	const CWithPointer* operator&() const;
};


int main(int argc, char** argv) {
	CWithPointer cwp1, cwp2;
	CWithPointer* pcwp3 = new CWithPointer();

	cwp2 = cwp1;

	delete pcwp3;

	return 0;
}
