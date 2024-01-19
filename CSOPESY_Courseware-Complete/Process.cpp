#include "Process.h"
#include "IOCommand.h"
#include "MathUtils.h"
#include "PrintCommand.h"

Process::Process(int pid, String name, RequirementFlags requirementFlags)
{
	this->pid = pid;
	this->name = name;
	this->commandCounter = 0;
	this->requirementFlags = requirementFlags;
	this->currentState = ProcessState::READY;
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
	this->commandList[this->commandCounter]->execute();
}

void Process::moveToNextLine()
{
	this->commandCounter++;
}

bool Process::isFinished() const
{
	return this->commandCounter == this->commandList.size();
}

int Process::getRemainingTime() const
{
	return this->commandList.size() - this->commandCounter;
}

int Process::getCommandCounter() const
{
	return this->commandCounter;
}

int Process::getLinesOfCode() const
{
	return this->commandList.size();
}

int Process::getPID() const
{
	return this->pid;
}

int Process::getCPUCoreID() const
{
	return this->cpuCoreID;
}

Process::ProcessState Process::getState() const
{
	return this->currentState;
}

String Process::getName() const
{
	return this->name;
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
