
#include <iostream>

// use forward declarations
class MathErr;

class IntOverflow : public MathErr {
public:
	IntOverflow() {}
	IntOverflow(const char* p, int a, int b) : op(p), a1(a), a2(b) {}
	virtual ~IntOverflow() {}
	virtual void debug_print() {
		std::cerr << "Integer overflow: " << 
			op << '(' << a1 << ',' << a2 << ')' << std::endl;
	}
private:
	const char* op;
	int a1, a2;
};