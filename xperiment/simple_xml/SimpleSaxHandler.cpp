#include "SimpleSaxHandler.hpp"
//#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/sax/AttributeList.hpp>

SimpleSaxHandler::SimpleSaxHandler()
{
}


//
// Implementations of the SAX DocumentHandler interface

void SimpleSaxHandler::startElement(
		const XMLCh* const name,
		AttributeList& attributes)
{
}

void SimpleSaxHandler::endElement(
		const XMLCh* const name)
{
}

void SimpleSaxHandler::characters(
		const XMLCh* const chars,
		const XMLSize_t length)
{
}

void SimpleSaxHandler::endDocument()
{
}

void SimpleSaxHandler::ignorableWhitespace(
		const XMLCh* const chars,
		const XMLSize_t length)
{
}

void SimpleSaxHandler::processingInstruction(
		const XMLCh* const target,
		const XMLCh* const data)
{
}

void SimpleSaxHandler::startDocument()
{
}

void SimpleSaxHandler::writeChars(
        const   XMLByte* const  toWrite)
{
}

void SimpleSaxHandler::writeChars(
        const   XMLByte* const toWrite,
		const XMLSize_t count,
		XMLFormatter* const formatter)
{
}
