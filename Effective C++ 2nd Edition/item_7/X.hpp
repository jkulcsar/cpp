#pragma once
#include <memory>

using namespace std;
class X
{
public:
	static new_handler set_new_handler( new_handler p);
	static void* operator new(size_t size);
	X(void);
	~X(void);
private:
	static new_handler currentHandler;
};
