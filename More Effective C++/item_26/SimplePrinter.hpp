#pragma once

namespace Printing
{
	class PrintJob;		// forward declaration

	class SimplePrinter
	{
	public:
		void submitJob(PrintJob&) {}
		void reset(){}
		void performSelfTest() {}
		// ...

		friend SimplePrinter& thePrinter();
	};

	//
	// because thePrinter() is a friend of SimplePrinter
	// it's not bound by restrictions imposed by private
	// ctors (can access private members/functions)
	SimplePrinter& thePrinter()
	{
		static SimplePrinter p;
		return p;
	};
} // end of Printing namespace
