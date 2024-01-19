#include "FCFSScheduler.h"
#include "AScheduler.h"
#include "ResourceEmulator.h"

FCFSScheduler::FCFSScheduler() : AScheduler(SchedulingAlgorithm::FCFS, 0, FCFS_SCHEDULER_NAME)
{

}

void FCFSScheduler::init()
{
	ResourceEmulator::getInstance()->startAllCPUs();
}

void FCFSScheduler::execute()
{
	ResourceEmulator* resourceEmulator = ResourceEmulator::getInstance();

	if(resourceEmulator->hasAvailableCPU())
	{
		if (!this->readyQueue.empty())
		{
			ResourceEmulator::getInstance()->scheduleCPUWork(this->readyQueue.front());
			this->readyQueue.pop();
		}
	}
	else
	{
		// this->outputBuffer << FCFS_SCHEDULER_NAME << "- Waiting for available CPU" << std::endl;
		// std::cout << this->outputBuffer.str() << std::endl;
	}

	// if (this->currentProcess == nullptr || this->currentProcess->isFinished())
	// {
	// 	if (!this->readyQueue.empty())
	// 	{
	// 		this->currentProcess = this->readyQueue.front();
	// 		this->readyQueue.pop();
	// 	}
	// }
	// else if (!this->currentProcess->isFinished())
	// {
	// 	//schedule to CPU
	// 	bool success = ResourceEmulator::getInstance()->scheduleCPUWork(this->currentProcess);
	// }
}
