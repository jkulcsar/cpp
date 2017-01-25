#pragma once

#include <string.h>

class SimpleString {
public:
	SimpleString() {
		data = new char[1];
		*data = '\0';
	}
	SimpleString(const char *value ) {
		if(value) {
			data = new char[strlen(value) + 1];
			strcpy(data, value);
		}
		else {
			data = new char[1];
			*data = '\0';
		}
	}

	SimpleString& operator=(const SimpleString& rhs) {
		// check for self-assignement
		if(this == &rhs)
			return *this;

		delete[] data;

		// must do a deep-copy of the data
		// don't just copy the value of the pointer
		data = new char[strlen(rhs.data) + 1];
		strcpy(data, rhs.data);

		return *this;
	}

	~SimpleString() {
		if(data)
			delete[] data;
	}

private:
	char *data;
};

