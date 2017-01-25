#include <iostream>

class MathErr {
public:
	MathErr() {}
	virtual ~MathErr() {}
	virtual void debug_print() {
		std::cerr << "Math error" << std::endl;
	}
};
