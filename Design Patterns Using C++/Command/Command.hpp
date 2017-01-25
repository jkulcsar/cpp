
#ifndef COMMAND_HPP_
#define COMMAND_HPP_

class Command {
public:
	virtual ~Command() {};
	virtual void Execute() = 0;
protected:
	Command() {};
};

#endif