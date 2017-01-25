#ifndef MACROCOMMAND_HPP_
#define MACROCOMMAND_HPP_

#include <list>
#include <algorithm>

#include "Command.hpp"

class MacroCommand : public Command {
public:
	MacroCommand();
	virtual ~MacroCommand();

	virtual void Add(Command*);
	virtual void Remove(Command*);

	virtual void Execute();
private:
	std::list<Command*> _commands;
};

void MacroCommand::Add(Command* cmd) {
	if(cmd)
		_commands.push_back(cmd);
}

void MacroCommand::Remove(Command* cmd) {
	std::list<Command*>::iterator pos = std::find(
		_commands.begin(),
		_commands.end(),
		cmd );

	if(pos != _commands.end())
		_commands.remove(cmd);

	// use remove_if() instead of the code above!
	//_commands.remove_if()
}


#endif

