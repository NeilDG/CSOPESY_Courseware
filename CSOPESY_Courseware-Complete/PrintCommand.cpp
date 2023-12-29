#include "PrintCommand.h"
#include "IETThread.h"

PrintCommand::PrintCommand(int pid, String& toPrint) : ICommand(pid, PRINT)
{
	this->toPrint = toPrint;
}

void PrintCommand::execute()
{
	ICommand::execute();
	std::cout << "PID " << this->pid << ":" << this->toPrint << std::endl;
}
