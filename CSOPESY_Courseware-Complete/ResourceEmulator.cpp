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

bool ResourceEmulator::scheduleCPUWork(std::shared_ptr<Process> process)
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
		availableCore->assignExecutable(process, this);
		availableCore->start();
		return true;
	}
	else
	{
		std::cerr << "Cannot schedule CPU work. All cores occupied." << std::endl;
		return false;
	}
}

bool ResourceEmulator::hasAvailableCPU()
{
	for (int i = 0; i < MAX_CPU_CORES; i++)
	{
		if (this->workingCores[i]->isAvailable() == false)
		{
			return false;
		}
	}

	return true;
}

void ResourceEmulator::onActionFinished(int cpuID)
{
	//reset the working cpu core
	this->mutex->acquire();
	// this->workingCores[cpuID] = nullptr;
	// this->workingCores[cpuID] = std::make_shared<CPUWorker>(cpuID);
	this->workingCores[cpuID]->available = true;
	this->mutex.release();
}

ResourceEmulator::ResourceEmulator()
{
	for(int i = 0; i < MAX_CPU_CORES; i++)
	{
		this->workingCores[i] = std::make_shared<CPUWorker>(i);
	}

	this->mutex = std::make_unique<IETSemaphore>(1);
}

CPUWorker::CPUWorker(int cpuID)
{
	this->cpuID = cpuID;
}

void CPUWorker::assignExecutable(std::shared_ptr<Process> process, IActionFinished* actionFinished, int quantumTimes)
{
	this->process = process;
	this->actionFinished = actionFinished;
	this->quantumTimes = quantumTimes;
}

void CPUWorker::run()
{
	//cpu start
	this->available = false;
	for(int i = 0; i < this->quantumTimes; i++)
	{
		if(this->process->getRemainingTime() > 0)
		{
			this->process->executeCurrentCommand();
			this->process->moveToNextLine();
		}
		else
		{
			break;
		}
	}

	//cpu end
	this->available = true;
	this->process = nullptr;
	this->actionFinished->onActionFinished(this->cpuID);
}

bool CPUWorker::isAvailable() const
{
	return this->available;
}
