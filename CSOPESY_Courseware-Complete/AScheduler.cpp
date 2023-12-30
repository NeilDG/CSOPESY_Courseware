#include "AScheduler.h"

AScheduler::AScheduler(SchedulingAlgorithm schedulingAlgo, int pid, String processName)
{
	this->schedulingAlgo = schedulingAlgo;
	this->pid = pid;
	this->processName = processName;
	this->running = true;
}

void AScheduler::run()
{
	while(this->running)
	{
		this->execute();
	}
}

void AScheduler::stop()
{
	this->running = false;
}
