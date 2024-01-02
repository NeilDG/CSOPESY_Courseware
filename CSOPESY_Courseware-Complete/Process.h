#pragma once
#include <memory>
#include <vector>
#include "ICommand.h"

class Process
{
public:
	Process(int pid);
	void addCommand(ICommand::CommandType commandType);
	void executeCurrentCommand() const;
	void moveToNextLine();

	bool isFinished() const;
	int getRemainingTime() const;
	int getPID() const;


	void test_generateRandomCommands(int limit);

private:
	int pid;
	typedef std::vector<std::shared_ptr<ICommand>> CommandList;
	CommandList commandList;

	int commandIndex;
};

