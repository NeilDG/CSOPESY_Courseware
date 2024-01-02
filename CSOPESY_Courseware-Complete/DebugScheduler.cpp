#include "DebugScheduler.h"
#include <iostream>

#include "AScheduler.h"
#include "IETThread.h"
#include "Process.h"
#include "GlobalConfig.h"

DebugScheduler::DebugScheduler() : AScheduler(SchedulingAlgorithm::DEBUG, 0, DEBUG_SCHEDULER_NAME)
{
}

void DebugScheduler::init()
{
}

/**
 * \brief Simply goes through the process queue and executes each process one by one
 */
void DebugScheduler::execute()
{
	if (this->currentProcess == nullptr || this->currentProcess->isFinished())
	{
		if (!this->processQueue.empty())
		{
			this->currentProcess = this->processQueue.front();
			this->processQueue.pop();
		}
	}
	else if (!this->currentProcess->isFinished())
	{
		this->currentProcess->executeCurrentCommand();
		this->currentProcess->moveToNextLine();
	}

	IETThread::sleep(Delay::PER_PROCESS_DELAY);
}
