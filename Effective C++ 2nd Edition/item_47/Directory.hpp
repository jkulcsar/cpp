#pragma once
#include "FileSystem.hpp"

class Directory
{
public:
	Directory(void) {
		//
		// create the directory object by calling
		// member functions on theFileSystem object
		//
	}
	virtual ~Directory(void) {}

	// just a test member function
	void ls();
};
