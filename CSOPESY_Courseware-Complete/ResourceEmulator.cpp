#include "ResourceEmulator.h"

ResourceEmulator* ResourceEmulator::sharedInstance = nullptr;
ResourceEmulator* ResourceEmulator::getInstance()
{
	return sharedInstance;
}

void ResourceEmulator::initialize()
{
	sharedInstance = new ResourceEmulator();
}

void ResourceEmulator::destroy()
{
	delete sharedInstance;
}

bool ResourceEmulator::scheduleCPUWork(IExecutableAction* executableAction)
{
	//find first available working core.
	std::shared_ptr<CPUWorker> availableCore = nullptr;
	for(int i = 0; i < MAX_CPU_CORES; i++)
	{
		if(this->workingCores[i]->isAvailable())
		{
			availableCore = this->workingCores[i];
			break;
		}
	}

	if(availableCore != nullptr)
	{
		availableCore->assignExecutable(executableAction, this);
		availableCore->start();
		return true;
	}
	else
	{
		std::cerr << "Cannot schedule CPU work. All cores occupied." << std::endl;
		return false;
	}
}

void ResourceEmulator::onActionFinished(int cpuID)
{
	//reset the working cpu core
	this->workingCores[cpuID] = nullptr;
	this->workingCores[cpuID] = std::make_shared<CPUWorker>(cpuID);
}

ResourceEmulator::ResourceEmulator()
{
	for(int i = 0; i < MAX_CPU_CORES; i++)
	{
		this->workingCores[i] = std::make_shared<CPUWorker>(i);
	}
}

CPUWorker::CPUWorker(int cpuID)
{
	this->cpuID = cpuID;
}

void CPUWorker::assignExecutable(IExecutableAction* executableAction, IActionFinished* actionFinished)
{
	this->executableAction = executableAction;
	this->actionFinished = actionFinished;
}

void CPUWorker::run()
{
	//cpu start
	this->available = false;
	this->executableAction->executeAction();

	//cpu end
	this->available = true;
	this->executableAction = nullptr;
	this->actionFinished->onActionFinished(this->cpuID);
}

bool CPUWorker::isAvailable() const
{
	return this->available;
}
