
#pragma once

class RCObject
{
public:
	RCObject();
	RCObject(const RCObject&);
	RCObject& operator=(const RCObject&);
	virtual ~RCObject();

	void addReference();
	void removeReference();

	void markUnshareable();
	bool isShareable() const;

	bool isShared() const;

private:
	int refCount;
	bool shareable;
};

// ctor
RCObject::RCObject() : refCount(0), shareable(true) {}

// copy ctor
RCObject::RCObject(const RCObject&) : refCount(0), shareable(true) {}

// assignement operator
RCObject& RCObject::operator =(const RCObject &)
{
	return *this;
}

// virtual dtors must be implemented
// even if they are pure virtual and do nothing
RCObject::~RCObject() {}

void RCObject::addReference()
{
	++refCount;
}

// not only decrements ref count but also
// deletes this object
// for this we must make sure these objects
// can be created on heap only!
void RCObject::removeReference()
{
	if(--refCount == 0)
		delete this;
}

void RCObject::markUnshareable()
{
	shareable = false;
}

bool RCObject::isShareable() const
{
	return shareable;
}

bool RCObject::isShared() const
{
	return refCount > 1;
}
