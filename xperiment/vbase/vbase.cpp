
#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

//
// From MSDN:
//Because a class can be an indirect base class to a derived class more than once, 
//C++ provides a way to optimize the way such base classes work. Virtual base classes 
// offer a way to save space and avoid ambiguities in class hierarchies that use multiple 
//inheritance. 
//
//Each nonvirtual object contains a copy of the data members defined in the base class. 
//This duplication wastes space and requires you to specify which copy of the base class 
//members you want whenever you access them.
//
//When a base class is specified as a virtual base, it can act as an indirect base more 
//than once without duplication of its data members. A single copy of its data members 
//is shared by all the base classes that use it as a virtual base.
//
//When declaring a virtual base class, the virtual keyword appears in the base lists 
//of the derived classes.
//


//From Stroustrup book:
//Constructors of base classes are not inherited by derived classes. 
//When an object of derived class type is created, 
//it is constructed starting with the base class components; 
//then it moves to the derived class components. 
//The compiler uses each base class's constructor as that part of 
//the complete object is initialized 
//(except in cases of virtual derivation, as described in Initializing Base Classes).

//The subobjects representing virtual base classes are initialized by the 
//constructor for the most derived class. That means that where virtual derivation 
//is specified, the most derived class must explicitly initialize 
//the virtual base class, or the virtual base class must have a default constructor. 
//Initializations for virtual base classes that appear in constructors for classes 
//other than the most derived class are ignored.
//


class Storable {
public:
	Storable( const string s) : store( s ) { 
		string message( "Storable::Storable(const string)" );
		message += s;
		cout << message << endl;
	};

	// why is the default constructor called and not the Storable(const string s) ?
	// see explanation(s) above !
//	Storable() { 
//		string message( "Storable::Storable()" );
//		cout << message << endl;
//	};
	
	virtual void read() = 0;
	virtual void write() = 0;
	const string& getStoreFileName()	{
		return store;
	};
	virtual ~Storable()	{
		string message( "Storable::~Storable()" );
		cout << message << endl;
	};
private:
	const string	store;

	Storable( const Storable& );
	Storable& operator=( const Storable& );
};

class Transmitter : public virtual Storable {
public:
	Transmitter( const string filename ) : Storable( filename ) { };
	void read()	{
		string	message( "Transmitter::read() from filename: " );
		message += getStoreFileName();
		cout << message << endl;
	};
	void write()	{
		string message( "Transmitter::write() to filename: " );
		message += getStoreFileName();
		cout << message << endl;
	};
};

class Receiver : public virtual Storable {
public:
	Receiver( const string filename ) : Storable( filename ) { };
	void read()	{
		string	message( "Receiver::read() from filename: " );
		message += getStoreFileName();
		cout << message << endl;
	};
	void write()	{
		string message( "Receiver::write() to filename: " );
		message += getStoreFileName();
		cout << message << endl;
	};
};


//The subobjects representing virtual base classes are initialized by the 
//constructor for the most derived class. That means that where virtual derivation 
//is specified, the most derived class must explicitly initialize 
//the virtual base class, or the virtual base class must have a default constructor. 
//Initializations for virtual base classes that appear in constructors for classes 
//other than the most derived class are ignored.

class Radio : public virtual Transmitter, public virtual Receiver {
//class Radio : public Transmitter, public Receiver {
public:
	Radio( const string filename ) : Storable( filename ), Transmitter( filename ), Receiver( filename ) { };
	void read()	{
		Transmitter::read();
		Receiver::read();
		string	message( "Radio::read() from filename: " );
		message += getStoreFileName();
		cout << message << endl;
	};
	void write()	{
		Transmitter::write();
		Receiver::write();
		string message( "Radio::write() to filename: " );
		message += getStoreFileName();
		cout << message << endl;
	};
};




int main( int argc , char** argv )
{
	const string store_radio = "store_radio";
	const string store_transmitter = "store_transmitter";
	const string store_receiver = "store_receiver";

	Transmitter	tr1( store_transmitter );
	Receiver	rc1( store_receiver );

	tr1.read();
	tr1.write();

	rc1.read();
	rc1.write();



	Radio r1(store_radio);
	r1.read();
	r1.write();

	Radio*	pr2	=	new Radio( "store_radio2" );
	pr2->read();
	pr2->write();
	if( pr2 )
		delete pr2;

	return 0;
}