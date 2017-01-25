#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/framework/XMLFormatter.hpp>

#include <stack>
#include <sstream>

#include "ElementData.h"


XERCES_CPP_NAMESPACE_USE

class MySaxHandler : public HandlerBase, private XMLFormatTarget
{
	const ElementMap_t& element_map_;
	std::stack<std::string> current_path_;
	std::ostringstream current_text_;

	void write_xml(
		std::ostringstream& target,
		const XMLCh* const s);

public:
	MySaxHandler(const ElementMap_t& map);

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
