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
	//create a working core if available
	this->mutex->acquire();
	if(this->hasAvailableCPU())
	{
		CPUWorker availableCore(this->numWorkingCores);
		availableCore.assignExecutable(process, this);
		// availableCore.start();

		this->numWorkingCores++;
		this->mutex->release();
		return true;
	}
	else
	{
		std::cerr << "Cannot schedule CPU work. All cores occupied." << std::endl;
		this->mutex->release();
		return false;
	}
}

bool ResourceEmulator::hasAvailableCPU() const
{
	return this->numWorkingCores < MAX_CPU_CORES;
}

void ResourceEmulator::onActionFinished(int cpuID)
{
	//reset the working cpu core
	this->mutex->acquire();
	this->numWorkingCores--;
	this->mutex->release();
}

ResourceEmulator::ResourceEmulator()
{
	this->numWorkingCores = 0;
	this->mutex = std::make_shared<IETSemaphore>(1);
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

	std::thread(&CPUWorker::run, this).detach(); //detach thread for independent execution. without this, join() function must be called.
}

void CPUWorker::run()
{
	//cpu start
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
	this->actionFinished->onActionFinished(this->cpuID);
}
