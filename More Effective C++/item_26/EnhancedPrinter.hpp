#pragma once

namespace Printing
{
	// forward declaration(s)
	class PrintJob;

	class EnhancedPrinter
	{
	public:
		// exception class, internal to the
		// EnhancedPrinter class
		class TooManyObjects{
		public:
			std::string what()
			{
				return "Request to create too many printers!";
			}
		};

		// pseudo-constructor
		static EnhancedPrinter * makePrinter();
		static EnhancedPrinter * makePrinter(EnhancedPrinter&);

		void submitJob(PrintJob&) {}
		void reset(){}
		void performSelfTest() {}
		// ...

		~EnhancedPrinter() {};
	
	private:

		// constructor and copy-ctor are private
		// this will guarantee no instnaces
		// and no inheritance from this class
		EnhancedPrinter();
		EnhancedPrinter(EnhancedPrinter&);


		// track number of objects
		// (reference counting pattern)
		static size_t numObjects;
		static const size_t maxObjects = 10;
	
	}; // end of EnhancedPrinter

	// obligatory definition of static objects
	size_t EnhancedPrinter::numObjects = 0;

	EnhancedPrinter::EnhancedPrinter()
	{
		if(numObjects >= maxObjects)
			throw TooManyObjects();

		// continue here with printer ctor/init

		++numObjects;
	}

	// pseudo-constructor
	EnhancedPrinter * EnhancedPrinter::makePrinter()
	{
		return new EnhancedPrinter();
	}

	EnhancedPrinter::EnhancedPrinter(EnhancedPrinter& rhs)
	{
		if(numObjects >= maxObjects)
			throw TooManyObjects();

		// continue here with printer ctor/init

		++numObjects;
	}

	// pseudo-constructor
	EnhancedPrinter * EnhancedPrinter::makePrinter(EnhancedPrinter& rhs)
	{
		return new EnhancedPrinter(rhs);
	}

} // end of Printing namespace
