#include "FCFSScheduler.h"
#include "AScheduler.h"
#include "ResourceEmulator.h"

FCFSScheduler::FCFSScheduler() : AScheduler(SchedulingAlgorithm::FCFS, 0, FCFS_SCHEDULER_NAME)
{

}

void FCFSScheduler::execute()
{
	const ResourceEmulator* resourceEmulator = ResourceEmulator::getInstance();

	if(resourceEmulator->hasAvailableCPU())
	{
		if (!this->processQueue.empty())
		{
			ResourceEmulator::getInstance()->scheduleCPUWork(this->processQueue.front());
			this->processQueue.pop();
		}
	}
	else
	{
		// this->outputBuffer << FCFS_SCHEDULER_NAME << "- Waiting for available CPU" << std::endl;
		// std::cout << this->outputBuffer.str() << std::endl;
	}

	// if (this->currentProcess == nullptr || this->currentProcess->isFinished())
	// {
	// 	if (!this->processQueue.empty())
	// 	{
	// 		this->currentProcess = this->processQueue.front();
	// 		this->processQueue.pop();
	// 	}
	// }
	// else if (!this->currentProcess->isFinished())
	// {
	// 	//schedule to CPU
	// 	bool success = ResourceEmulator::getInstance()->scheduleCPUWork(this->currentProcess);
	// }
}
