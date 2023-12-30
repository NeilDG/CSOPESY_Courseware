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
	void test_storeRandomProcessesInQueue(int limit);
	String getLatestMsg();

	struct ProcessTimeInfo
	{
		int pid;
		int remainingTime;
	};

	std::vector<ProcessTimeInfo> getAllProcessRemainingTime() const;

private:
	std::shared_ptr<Process> currentProcess = nullptr;
	std::stringstream outputBuffer;
};

