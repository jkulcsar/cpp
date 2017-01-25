#ifndef PASTECOMMAND_HPP_
#define PASTECOMMAND_HPP_

#include "Application.hpp"
#include "Document.hpp"

#include "Command.hpp"

class PasteCommand {
public:
	PasteCommand(Document* doc) : _document(doc) {
	}
	virtual void Execute() {
		_document->Paste();
	}	
private:
	Document* _document;
};

#endif
