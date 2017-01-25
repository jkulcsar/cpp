#ifndef OPENCOMMAND_HPP_
#define OPENCOMMAND_HPP_

#include "Application.hpp"
#include "Document.hpp"

#include "Command.hpp"

class Application;

class OpenCommand : public Command {
public:
	OpenCommand(Application*);
	virtual void Execute();
protected:
	virtual const char* AskUser();
private:
	Application* _application;
	char* _response;
};

OpenCommand::OpenCommand(Application* a) {
	_application = a;
}

void OpenCommand::Execute() {
	const char* name = AskUser();

	if(name != 0) {
		Document* document = new Document(name);
		_application->Add(document);
		document->Open();
	}
}

const char* OpenCommand::AskUser() {
	return 0;
}

#endif
