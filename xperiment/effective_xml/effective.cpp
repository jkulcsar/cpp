#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/parsers/SAXParser.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

#include "ElementData.h"
#include "MySaxHandler.hpp"
#include "StrX.hpp"

XERCES_CPP_NAMESPACE_USE

template<typename T>
void AddElement(ElementMap_t& map, T& ref, const std::string& path)
{
	map.insert(std::make_pair(path, new ElementData<T>(ref)));
}


void Show(ElementMap_t& map)
{
	ElementMap_t::const_iterator i;

	std::cout << "CURRENT STATE OF MAP of ELEMENTS:" << std::endl;
	for(i = map.begin(); i != map.end(); ++i)
		std::cout << i->first << "--" << i->second->get() << std::endl;
	std::cout << std::endl;
}

int main( int argc, char* argv[] )
{
	char xmlFile[] = "file.xml";

	int errorCount = 0;
	int errorCode = 0;

    // Initialize the XML4C2 system
    try
    {
         XMLPlatformUtils::Initialize();
    }

    catch (const XMLException& toCatch)
    {
         XERCES_STD_QUALIFIER cerr << "Error during initialization! :\n"
              << StrX(toCatch.getMessage()) << XERCES_STD_QUALIFIER endl;
         return 1;
    }


	//
	// store each individual data item in a separate variable,
	// each with its own ElementData object with the template 
	// instantiated for the appropriate type:
	std::string FirstName;
	std::string LastName;
	struct Date {
		int year, month, day;
	};
	Date dob;

	//
	// initialize 
	FirstName.empty();
	LastName.empty();
	dob.year = 0;
	dob.month = 0;
	dob.day = 0;

	ElementMap_t element_map;

	//
	// the following structue for holding data should be created from metadata
	// here: hardcoded only
	// use this is a reference to valid map key definitions!
	AddElement(element_map, FirstName, "/People/Person/FirstName");
	AddElement(element_map, LastName, "/People/Person/LastName");
	AddElement(element_map, dob.year, "/People/Person/DateOfBirth/Year");
	AddElement(element_map, dob.month, "/People/Person/DateOfBirth/Month");
	AddElement(element_map, dob.day, "/People/Person/DateOfBirth/Day");

	Show(element_map);

	SAXParser* parser = new SAXParser;
	try
	{
		MySaxHandler handler(element_map);

		parser->setDocumentHandler(&handler);
        parser->setErrorHandler(&handler);
		parser->parse(xmlFile);
		errorCount = parser->getErrorCount();
	}
	catch (const OutOfMemoryException&)
	{
		XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
		errorCode = 5;
	}
	catch (const XMLException& toCatch)
	{
		XERCES_STD_QUALIFIER cerr << "\nAn error occurred\n  Error: "
			<< StrX(toCatch.getMessage())
			<< "\n" << XERCES_STD_QUALIFIER endl;
		errorCode = 4;
	}

	Show(element_map);

    //
    //  Delete the parser itself.  Must be done prior to calling Terminate, below.
    //
    delete parser;

    // And call the termination method
    XMLPlatformUtils::Terminate();

    if (errorCount > 0)
        return 4;
    else
        return 0;
}
