#pragma once
#include "RCObject.hpp"
#include "RCPtr.hpp"



#include <string.h>

class String {
public:
	//
	// constructor w/parameter
	String(const char *value = "");

	const char& operator[](int index) const;
	char& operator[](int index);

private:
  // class representing string values
  struct StringValue: public RCObject {
    char *data;

    StringValue(const char *initValue);
    StringValue(const StringValue& rhs);
    void init(const char *initValue);
    ~StringValue();
  };

  RCPtr<StringValue> value;
};

//
// implementation of String::StringValue
//
void String::StringValue::init(const char *initValue)
{
  data = new char[strlen(initValue) + 1];
  strcpy(data, initValue);
}
String::StringValue::StringValue(const char *initValue)
{
	init(initValue);
}
String::StringValue::StringValue(const StringValue& rhs)
{
	init(rhs.data);
}
String::StringValue::~StringValue()
{
	delete [] data;
}

//
// implementation of String
//
String::String(const char *initValue) : value(new StringValue(initValue)) {}

const char& String::operator[](int index) const
{
	return value->data[index];
}
char& String::operator[](int index)
{
  if (value->isShared()) {
    value = new StringValue(value->data);
  }
  value->markUnshareable();
  return value->data[index];
}
