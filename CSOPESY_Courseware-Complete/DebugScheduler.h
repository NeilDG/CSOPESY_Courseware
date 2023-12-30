#pragma once
#include <memory>
#include <queue>
#include <sstream>
#include "Process.h"

class DebugScheduler
{
public:
	DebugScheduler() = default;

	void test_storeRandomProcessesInQueue(int limit);
	void execute();
	String getLatestMsg();

	struct ProcessTimeInfo
	{
		int pid;
		int remainingTime;
	};

	std::vector<ProcessTimeInfo> getAllProcessRemainingTime() const;

private:
	typedef std::queue<std::shared_ptr<Process>> ProcessQueue;
	typedef std::vector<std::shared_ptr<Process>> ProcessList;

	ProcessQueue processQueue;
	ProcessList processList;
	std::shared_ptr<Process> currentProcess = nullptr;

	std::stringstream outputBuffer;
};

