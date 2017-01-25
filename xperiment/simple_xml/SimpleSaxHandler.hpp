#pragma once

#include    <xercesc/sax/HandlerBase.hpp>
#include    <xercesc/framework/XMLFormatter.hpp>

#include <stack>
#include <sstream>

XERCES_CPP_NAMESPACE_USE

class SimpleSaxHandler : public HandlerBase, private XMLFormatTarget
{

public:
	SimpleSaxHandler();

    // -----------------------------------------------------------------------
    //  Implementations of the format target interface
    // -----------------------------------------------------------------------
    void writeChars(
        const   XMLByte* const  toWrite);

    void writeChars(
        const   XMLByte* const  toWrite,
		const XMLSize_t    count,
		XMLFormatter* const   formatter);


	//
	// Implementations of the SAX DocumentHandler interface
	void endDocument();

    void ignorableWhitespace(
		const XMLCh* const chars,
		const XMLSize_t length);

    void processingInstruction(
		const XMLCh* const target,
		const XMLCh* const data);

    void startDocument();

	void startElement(
		const XMLCh* const name,
		AttributeList& attributes);

	void endElement(
		const XMLCh* const name);

	void characters(
		const XMLCh* const chars,
		const XMLSize_t length);
};
