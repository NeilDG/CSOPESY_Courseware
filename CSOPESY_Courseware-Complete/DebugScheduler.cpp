#include "DebugScheduler.h"
#include <iostream>
#include "IETThread.h"
#include "Process.h"
#include "GlobalConfig.h"

void DebugScheduler::test_storeRandomProcessesInQueue(int limit)
{
	for(int i = 0; i < limit; i++)
	{
		std::shared_ptr<Process> p = std::make_shared<Process>(i + 1);
		p->test_generateRandomCommands(10);
		this->processQueue.push(p);
		this->processList.push_back(p);
	}
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

std::vector<DebugScheduler::ProcessTimeInfo> DebugScheduler::getAllProcessRemainingTime() const
{
	std::vector<DebugScheduler::ProcessTimeInfo> ptList;
	for(int i = 0; i < this->processList.size(); i++)
	{
		ProcessTimeInfo pt{ this->processList[i]->getPID(), this->processList[i]->getRemainingTime() };
		ptList.push_back(pt);
	}

	return ptList;
}
