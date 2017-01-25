#pragma once

#include <string.h>

class RCString {
public:
	//
	// constructor w/parameter
	RCString(const char *initValue) : value(new StringValue(initValue)) {
	}

	//
	// copy constructor
	RCString(RCString& rhs) : value(rhs.value)
	{
		if(rhs.value->shareable)
		{
			// shareable, just increment the refcount
			value = rhs.value;
			++value->refCount;
		}
		else
		{
			// not shareable, create a new copy of the value
			value = new StringValue(rhs.value->data);
		}
	}

	//
	// assignement operator
	// for s1=s2 case
	RCString& operator=(RCString& rhs) {
		//
		// check for self-assignement must look at the
		// actual data; do nothing if they are the same 
		if(value == rhs.value)
			return *this;

		//
		// decrement reference counter
		// since s1 will no longer have that value
		if( --value->refCount == 0 )
			delete value;

		value = rhs.value;
		++value->refCount;

		return *this;
	}

	//
	// the const version of the index operator is straightforward
	// since it's read-only
	const char& operator[](int index) const {
		return value->data[index];
	}

	//
	// the non-const version of the index operator
	char& operator[](int index) {
		// if the value is shared, we must break-off
		// a separate copy of the value for this object
		if(value->refCount > 1) {
			--value->refCount;		// decrement the ref count
									// of the cuirrent value since
									// we won't be using it
			value = new StringValue(value->data);	// make a copy for this object
		}

		// must set the shareable flag to false
		// since the op[] was most likely called for
		// write/modify the value so from this point on
		// this string is not shareable
		value->shareable = false;

		return value->data[index];
	}

	~RCString()
	{
		if( --value->refCount == 0 )
			delete value;
	}

private:
	struct StringValue {
		int refCount;
		bool shareable;
		char *data;

		StringValue(const char *initValue);
		~StringValue();
	};
	StringValue *value;
};


RCString::StringValue::StringValue(const char *initValue) : refCount(1), shareable(true)
{
	data = new char[strlen(initValue) + 1];
	strcpy(data, initValue);
}

RCString::StringValue::~StringValue()
{
	delete [] data;
}

