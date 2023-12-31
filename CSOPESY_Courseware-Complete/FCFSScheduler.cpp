#include "FCFSScheduler.h"
#include "AScheduler.h"

FCFSScheduler::FCFSScheduler() : AScheduler(SchedulingAlgorithm::FCFS, 0, FCFS_SCHEDULER_NAME)
{

}

void FCFSScheduler::execute()
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
		//schedule to CPU
		ResourceEmulator::getInstance()->scheduleCPUWork(this);
	}
}

//TODO: Revise such that the process is assigned to the CPU itself.
void FCFSScheduler::executeAction()
{
	//work to be done in CPU
	this->currentProcess->executeCurrentCommand();
	this->currentProcess->moveToNextLine();
}

String FCFSScheduler::getLatestMsg()
{
}
