//
// Covariant return types
// Another approach, based on the C++ Common Knowledge book (item 31)
//
// Generally, an overriding function must have exactly the same return type
// as the function it overrides;
// This rule is relaxed for one particular situation:
// if B is a class type and one of its virtual functions returns B*,
// then in a derived from B class (D class) we can have an overriding virtual
// function that returns D*; same applies if returns are B& and D&.
//

//
// Illustrated by the classic Shape hierarchy, notice how the return type
// of the clone() virtual function is different, within the constraint that
// the return type must be in the inheritance chain
//

#include <memory>
#include <iostream>

class Shape {
  public:
    //...
    virtual Shape *clone() const = 0; // Prototype
    //...
	virtual ~Shape() {}
};

class Circle : public Shape {
  public:
	  virtual Circle *clone() const {
		  return new Circle(*this);
	  }
	  Circle(double r) : radius_(r) {
	  }
	  Circle() : radius_(0) {
	  }
	  virtual ~Circle() {}

    //...
private:
	double radius_;
};



int main(int argc, char** argv) {
	std::auto_ptr<Circle> c1(new Circle(2.0));
	std::auto_ptr<Circle> c2(c1->clone());

	return 0;
}
