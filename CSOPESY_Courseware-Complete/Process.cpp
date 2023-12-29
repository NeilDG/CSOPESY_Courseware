#include "Process.h"
#include "IOCommand.h"
#include "MathUtils.h"
#include "PrintCommand.h"

Process::Process(int pid)
{
	this->pid = pid;
	this->commandIndex = 0;
}

void Process::addCommand(ICommand::CommandType commandType)
{
	if(commandType == ICommand::IO)
	{
		const std::shared_ptr<ICommand> io = std::make_shared<IOCommand>(this->pid);
		this->commandList.push_back(io);
	}
	else
	{
		String toPrint = "This is a sample print.";
		const std::shared_ptr<ICommand> print = std::make_shared<PrintCommand>(this->pid, toPrint);
		this->commandList.push_back(print);
	}
}

void Process::executeCurrentCommand() const
{
	this->commandList[this->commandIndex]->execute();
}

void Process::moveToNextLine()
{
	this->commandIndex++;
}

bool Process::isFinished() const
{
	return this->commandIndex == this->commandList.size();
}
int Process::getPID() const
{
	return this->pid;
}

void Process::test_generateRandomCommands(int limit)
{
	for(int i = 0; i < limit; i++)
	{
		int rand = MathUtils::randomInt(0, 3);
		if(rand == 0)
		{
			this->addCommand(ICommand::IO);
		}
		else
		{
			this->addCommand(ICommand::PRINT);
		}
	}
}
