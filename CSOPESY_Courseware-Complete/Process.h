#pragma once
#include <memory>
#include <vector>
#include "ICommand.h"
#include "TypedefRepo.h"

class Process
{
public:
	struct RequirementFlags
	{
		bool requireFiles;
		int numFiles;
		bool requireMemory;
		int memoryRequired;
	};

	struct CommandInfo
	{
		int currentCounter;
		int linesOfCode;
	};

	Process(int pid, String name, RequirementFlags requirementFlags);
	void addCommand(ICommand::CommandType commandType);
	void executeCurrentCommand() const;
	void moveToNextLine();

	bool isFinished() const;
	int getRemainingTime() const;
	int getPID() const;
	String getName() const;
	CommandInfo getCurrentCommandInfo() const;

	void test_generateRandomCommands(int limit);

private:
	int pid;
	String name;
	typedef std::vector<std::shared_ptr<ICommand>> CommandList;
	CommandList commandList;

	int commandCounter;
	RequirementFlags requirementFlags;
};

