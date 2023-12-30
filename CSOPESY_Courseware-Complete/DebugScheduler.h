#pragma once
#include <memory>
#include <queue>
#include <sstream>
#include "AScheduler.h"
#include "Process.h"

class DebugScheduler : public AScheduler
{
public:
	DebugScheduler();
	void execute() override;
	String getLatestMsg();

private:
	std::shared_ptr<Process> currentProcess = nullptr;
	std::stringstream outputBuffer;
};

