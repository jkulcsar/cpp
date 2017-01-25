
#pragma once

//
// a class to represent unlimited precision numbers (UPNumber)

namespace UPN
{
	//
	// to restrict creating UPNumber classes only on the heap
	// we need to make the destructor protected or private;
	// if protected, this class can be used as a base class!
	// all constructors should be made private but this is overkill.

	class UPNumber
	{
	public:
		UPNumber()  {
			value_.intValue = 0;
		}
		UPNumber(int initValue) {
			value_.intValue = initValue;
		}
		UPNumber(double initValue) {
			value_.doubleValue = initValue;
		}
		UPNumber(UPNumber& rhs) {}

		//
		// pseudo-destructor;
		// const member function because even const objects
		// may be destroyed
		void destroy() const { delete this; }

	protected:
		~UPNumber() {}
	
	private:
		union NumberType
		{
			int intValue;
			double doubleValue;
		} value_;

	};

	class NonNegativeUPNumber : public UPNumber
	{
		//
		// derived classes have access to protected ctor and/or dtor
	};
}

class Assett
{
public:
	Assett() {};
	Assett(Assett&);
private:
	UPN::UPNumber *upn;
};
