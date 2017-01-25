#pragma once

template<typename BeingCounted>
class Counted
{
public:
	// exception class, internal to the
	// each class created from this template
	class TooManyObjects{
	public:
		std::string what()
		{
			return "Request to create too many printers!";
		}
	};

	static size_t objectCount()	{ return numObjects; }

protected:
	Counted();
	Counted(Counted&);

	~Counted() { --numObjects; }

private:
	static size_t numObjects;
	static const size_t maxObjects;

	void init(); // to avoid code duplication in ctors
};

// obligatory definition of static objects
template<typename BeingCounted>
size_t Counted<BeingCounted>::numObjects = 0;

template<typename BeingCounted>
Counted<BeingCounted>::Counted()
{
	init();
}

template<typename BeingCounted>
Counted<BeingCounted>::Counted(Counted<BeingCounted> &)
{
	init();
}

template<typename BeingCounted>
void Counted<BeingCounted>::init()
{
	if (numObjects >= maxObjects) throw TooManyObjects();
	++numObjects;
}
