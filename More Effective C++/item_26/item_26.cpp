
//
// Item 26: Limiting the number of objects of a class
//
// Allowing zero or one objects:
// Zero: just make the constructor and copy-constructor private
// One: by having the ctors private we can loosen the no-instance
// restrictions by instance counting and returning the one instance
// always fo subsequent requests.
//
//

#include <iostream>
#include <string>
#include <memory>

#include "SimplePrinter.hpp"
#include "EnhancedPrinter.hpp"
#include "Printer.hpp"
#include "PrintJob.hpp"

//#include "Counted.hpp"

using namespace std;

class CanNotBeInstantiated
{
	CanNotBeInstantiated();
	CanNotBeInstantiated(CanNotBeInstantiated&);
};


int main(int argc, char** argv)
{
	string stuffToPrint;
	// ... put stuff in this buffer
	stuffToPrint.append("Stuff ");
	stuffToPrint.append("to print!");

	Printing::PrintJob pj(stuffToPrint);

	Printing::thePrinter().reset();
	Printing::thePrinter().submitJob(pj);

	try
	{
		// create and use EnhancedPrinter
		auto_ptr<Printing::EnhancedPrinter> ep(Printing::EnhancedPrinter::makePrinter());
		ep->reset();
		ep->performSelfTest();
		ep->submitJob(pj);

		// create and use another EnhancedPrinter
		auto_ptr<Printing::EnhancedPrinter> aep(Printing::EnhancedPrinter::makePrinter());
		aep->reset();
		aep->performSelfTest();
		aep->submitJob(pj);

		// this is interesting: although the copy ctor of EnhancedPrinter is private
		// you can still copy-construct auto_ptr objects of EnhancedPrinter
		auto_ptr<Printing::EnhancedPrinter> yaep(ep);
		yaep->reset();

		// create yet another EnhancedPrinter, this time by copying an existing one
		//auto_ptr<Printing::EnhancedPrinter> ep2(Printing::EnhancedPrinter::makePrinter(*ep));
		//ep2->reset();
		//ep2->performSelfTest();
	}
	catch(Printing::EnhancedPrinter::TooManyObjects& ex)
	{
		cout << ex.what() << endl;
	}

	try
	{
		auto_ptr<Printing::Printer> printer1(Printing::Printer::makePrinter());
		printer1->reset();
		printer1->performSelfTest();
		printer1->submitJob(pj);
		
	}
	catch(Printing::Printer::TooManyObjects& ex)
	{
		cout << ex.what() << endl;
	}

	return 0;
}