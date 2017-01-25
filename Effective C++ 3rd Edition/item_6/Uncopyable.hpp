
#pragma once

class Uncopyable {
protected:
	// by keeping ctor/dtor protected will allow ctor/dtor of derived objects
	Uncopyable() {}
	~Uncopyable() {}
private:
	// ... but prevent copying, inlcuding copying of derived objects
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);
};
