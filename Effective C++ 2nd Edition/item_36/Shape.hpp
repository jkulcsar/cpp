#pragma once
#include <string>

using namespace std;

class Shape
{
public:
	Shape(void);
	virtual ~Shape(void);
	virtual void draw() const = 0;
	virtual void error(const string& message);
	int objectID() const;
private:
	int id_;
};
