#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/parsers/SAXParser.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

#include "SimpleSaxHandler.hpp"

#include <iostream>
#include "StrX.hpp"

XERCES_CPP_NAMESPACE_USE

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


	SAXParser* parser = new SAXParser;
//    parser->setValidationScheme();
    parser->setDoNamespaces(false);
    parser->setDoSchema(false);
    parser->setValidationSchemaFullChecking(false);

	try
	{
		SimpleSaxHandler handler;

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
