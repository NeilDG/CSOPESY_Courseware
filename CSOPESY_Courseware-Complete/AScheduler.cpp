#include "AScheduler.h"

AScheduler::AScheduler(SchedulingAlgorithm schedulingAlgo, int pid, String processName)
{
	this->schedulingAlgo = schedulingAlgo;
	this->pid = pid;
	this->processName = processName;
	this->running = true;
}

void AScheduler::addProcess(std::shared_ptr<Process> process)
{
	this->readyQueue.push(process);
	this->processList.push_back(process);
	this->processMap[process->getName()] = process;
}

std::shared_ptr<Process> AScheduler::findProcess(String processName)
{
	if(this->processMap.contains(processName)) {
		return this->processMap[processName];
	}
	else
	{
		// std::cout << "Process " << processName << " not found in " << this->getName() << std::endl;
		return nullptr;
	}
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


