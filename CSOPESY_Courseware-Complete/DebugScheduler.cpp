#include "DebugScheduler.h"
#include <iostream>
#include "IETThread.h"
#include "Process.h"
#include "GlobalConfig.h"

DebugScheduler::DebugScheduler()
{
}

void DebugScheduler::test_storeRandomProcessesInQueue(int limit)
{
	for(int i = 0; i < limit; i++)
	{
		std::shared_ptr<Process> p = std::make_shared<Process>(i + 1);
		p->test_generateRandomCommands(10);
		this->processQueue.push(p);
	}
}

/**
 * \brief Simply goes through the process queue and executes each process one by one
 */
void DebugScheduler::execute()
{

	while(!this->processQueue.empty())
	{
		std::shared_ptr<Process> p = this->processQueue.front();
		this->processQueue.pop();

		while(!p->isFinished())
		{
			p->executeCurrentCommand();
			p->moveToNextLine();
		}

		IETThread::sleep(Delay::PER_PROCESS_DELAY);
	}
}
