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

std::vector<AScheduler::ProcessTimeInfo> AScheduler::getAllProcessRemainingTime() const
{
	std::vector<ProcessTimeInfo> ptList;
	for (int i = 0; i < this->processList.size(); i++)
	{
		ProcessTimeInfo pt{ this->processList[i]->getPID(), this->processList[i]->getRemainingTime() };
		ptList.push_back(pt);
	}

	return ptList;
}

String AScheduler::getName()
{
	return this->processName;
}

String AScheduler::getLatestMsg()
{
	String displayMsg = this->outputBuffer.str();
	this->outputBuffer.str(std::string());
	return displayMsg;
}

void AScheduler::test_storeRandomProcessesInQueue(int limit)
{
	for (int i = 0; i < limit; i++)
	{
		std::shared_ptr<Process> p = std::make_shared<Process>(i + 1);
		p->test_generateRandomCommands(100);
		this->processQueue.push(p);
		this->processList.push_back(p);
	}
}
