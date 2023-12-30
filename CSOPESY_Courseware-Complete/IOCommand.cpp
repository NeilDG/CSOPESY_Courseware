#include "IOCommand.h"
#include "IETThread.h"
#include "GlobalConfig.h"
#include "MessageBuffer.h"

IOCommand::IOCommand(int pid) : ICommand(pid, IO)
{
}

void IOCommand::execute()
{
	ICommand::execute();
	// std::cout << "PID " << this->pid << ":" << "This is a sample I/O command." << std::endl;
	std::stringstream msg; msg << String("PID ") << this->pid << ":" << "This is a sample I/O command." << std::endl;
	MessageBuffer::log(msg.str());
}

