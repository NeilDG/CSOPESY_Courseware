#pragma once
#include <sstream>
#include "AScheduler.h"
#include "ResourceEmulator.h"

class FCFSScheduler :    public AScheduler, public IExecutableAction
{
public:
	FCFSScheduler();
	void execute() override;
	void executeAction() override;
	String getLatestMsg();

private:
	std::shared_ptr<Process> currentProcess = nullptr;
	std::stringstream outputBuffer;
};

