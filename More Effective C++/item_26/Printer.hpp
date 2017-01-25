
#pragma once

#include "Counted.hpp"

namespace Printing
{
	class Printer: private Counted<Printer> {
	public:
		// pseudo-constructors
		static Printer * makePrinter() { return new Printer(); }
		static Printer * makePrinter(const Printer& rhs) { return new Printer(rhs); }

		~Printer() { 
			// destroy logic (if any) here
		}

		void submitJob(const PrintJob& job) {}
		void reset() {}
		void performSelfTest() {}
		// ...

		using Counted<Printer>::objectCount;     // see below
		using Counted<Printer>::TooManyObjects;  // see below

	private:
		Printer();
		Printer(const Printer& rhs);
	};

	//
	// the init of the maximum number of instances
	// should be class specific
	// here: Printer class allows a max of 10
	// or class FileDescriptor could init this static
	// to some other value
	//const size_t Counted<FileDescriptor>::maxObjects = 256;

	//const size_t Counted<Printer>::maxObjects = 10;

	Printer::Printer()
	{
		// no need to do any instance counting
		// just proceed with normal printer init
	}

	Printer::Printer(const Printer& rhs)
	{
		// no need to do any instance counting
		// just proceed with normal printer init
	}


} // end of Printing namespace in this file

const size_t Counted<Printing::Printer>::maxObjects = 10;