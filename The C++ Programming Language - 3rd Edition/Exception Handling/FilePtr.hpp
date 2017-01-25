#pragma once
#include <stdio.h>

class FilePtr
{
	FILE* p;
	FilePtr(void) {} // make default ctor private
public:
	FilePtr(const char* n, const char* a) { p = fopen(n,a); }
	FilePtr(FILE* pp) : p(pp) {};
	virtual ~FilePtr(void) { fclose(p); }

	operator FILE*() {return p; }
};
