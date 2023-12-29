#pragma once
#include <memory>
#include <queue>

#include "Process.h"

class DebugScheduler
{
public:
	DebugScheduler();

	void test_storeRandomProcessesInQueue(int limit);
	void execute();

private:
	typedef std::queue<std::shared_ptr<Process>> ProcessQueue;
	ProcessQueue processQueue;
};

