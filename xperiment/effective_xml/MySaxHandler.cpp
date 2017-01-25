#include "MySaxHandler.hpp"
#include "StrX.hpp"

MySaxHandler::MySaxHandler(const ElementMap_t &map) : element_map_(map)
{
}

void MySaxHandler::write_xml(
		std::ostringstream& target,
		const XMLCh* const s)
{
	char *p = XMLString::transcode(s);
	target << p;
//	delete[] p;
}


//
// Implementations of the SAX DocumentHandler interface

void MySaxHandler::startElement(
		const XMLCh* const name,
		AttributeList& attributes)
{
	std::ostringstream this_path;
	if(!current_path_.empty())
		this_path << current_path_.top();
	this_path << '/';
//	write_xml(this_path, name);
	this_path << StrX(name);
	current_path_.push(this_path.str());
}

void MySaxHandler::endElement(
		const XMLCh* const name)
{
	if(!current_path_.empty())
	{
		ElementMap_t::const_iterator i = element_map_.find(current_path_.top());
		if( i != element_map_.end())
		{
			i->second->put(current_text_.str());
		}
	/*AddElement(element_map, FirstName, "/People/Person/FirstName");
	AddElement(element_map, LastName, "/People/Person/LastName");
	AddElement(element_map, dob.year, "/People/Person/DateOfBirth/Year");
	AddElement(element_map, dob.month, "/People/Person/DateOfBirth/Month");
	AddElement(element_map, dob.day, "/People/Person/DateOfBirth/Day");
*/
		current_path_.pop();
		current_text_.str("");
	}
}

void MySaxHandler::characters(
		const XMLCh* const chars,
		const XMLSize_t length)
{
//	write_xml(current_text_, chars);
	current_text_ << StrX(chars);
}

void MySaxHandler::endDocument()
{
}

void MySaxHandler::ignorableWhitespace(
		const XMLCh* const chars,
		const XMLSize_t length)
{
}

void MySaxHandler::processingInstruction(
		const XMLCh* const target,
		const XMLCh* const data)
{
}

void MySaxHandler::startDocument()
{
}

void MySaxHandler::writeChars(
        const   XMLByte* const  toWrite)
{
}

void MySaxHandler::writeChars(
        const   XMLByte* const toWrite,
		const XMLSize_t count,
		XMLFormatter* const formatter)
{
}
