//
// Item 25: Virtualizing constructors and non-member functions.
//
// virtual copy constructor: just return a self-copy,
// invoking the copy constructor (e.g. clone())
//
// making non-member functions act as virtual:
// (1)	define virtual functions in the base classes
// (2)	define a non-member function that does nothing else
//		but call the virtual functions
// to avoid the cost of function-calling, inline the non-member function
// (this is the classic scheme to implement opeartor << )
//
#include <list>
#include <iostream>

using namespace std;

//
// NewsLetterComponet
class NLComponent
{
private:
	// ...
public:
	//
	// virtual copy constructor: just return a self-copy,
	// invoking the copy constructor
	virtual NLComponent* clone() const  = 0;
	virtual ostream& print(ostream&) const = 0;
};

class TextBlock : public NLComponent
{
	// ...

	virtual ostream& print(ostream& s) const
	{
		// simple default impl. here
		return s;
	}

	// virtual copy constructor: just return a self-copy,
	// invoking the copy constructor
	virtual TextBlock* clone() const
	{
		return new TextBlock(*this);
	}
};

class GraphicBlock : public NLComponent
{
	// ...

	virtual ostream& print(ostream& s) const
	{
		// simple default impl. here
		return s;
	}

	// virtual copy constructor: just return a self-copy,
	// invoking the copy constructor
	virtual GraphicBlock* clone() const
	{
		return new GraphicBlock(*this);
	}
};

//
// making non-member functions act as virtual:
// (1)	define virtual functions in the base classes
// (2)	define a non-member function that does nothing else
//		but call the virtual functions
// to avoid the cost of function-calling, inline the non-member function
inline ostream& operator<< (ostream& s, NLComponent& nlc)
{
	return nlc.print(s);
}


class NewsLetter
{
public:
	// load a newsletter from a stream
	NewsLetter(istream& str);

	// copy constructor
	NewsLetter(NewsLetter&);

private:
	list<NLComponent*> components;

	// here readComponent is a 'virtual constructor'
	// because it will create objects of different type,
	// depending on what it reads from the disk
	static NLComponent* readComponent(istream& str);
};

NewsLetter::NewsLetter(std::istream &str)
{
	while(str)
	{
		// read next component from stream and
		// add the object to the component list
		components.push_back(readComponent(str));
	}
}

NLComponent* NewsLetter::readComponent(std::istream &str)
{
	NLComponent *nlc = new TextBlock();
	//or:
	//NLComponent *nlc = new GraphicBlock();

	// read from str stream into the newly created NLComponent
	return nlc;
}

//
// the existence of virtual copy constructors for it's elements
// makes it possible to write a normal (simple) copy constructor
// for the NewsLetter type
NewsLetter::NewsLetter(NewsLetter &rhs)
{
	// iterate over rhs's list to copy the elements in the list
	// into the components list for this object
	// eseentially: a proper deep-copy, no reference counting here though
	list<NLComponent*>::iterator pos;
	for(pos = components.begin(); pos != components.end(); ++pos)
		components.push_back((*pos)->clone());
}

int main(int argc, char** argv)
{
	NewsLetter nl;

	return 0;
}