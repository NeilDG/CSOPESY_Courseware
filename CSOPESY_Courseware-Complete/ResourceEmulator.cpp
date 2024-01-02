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

void ResourceEmulator::startAllCPUs()
{
	for (int i = 0; i < MAX_CPU_CORES; i++)
	{
		this->workingCores[i]->start();
		// std::cout << "Started CPU: " << i << std::endl;
	}
}

bool ResourceEmulator::scheduleCPUWork(std::shared_ptr<Process> process)
{
	//create a working core if available
	this->mutex->acquire();
	if(this->hasAvailableCPU())
	{
		std::shared_ptr<CPUWorker> availableCore = this->findFirstAvailableCPU();
		availableCore->assignExecutable(process.get(), this);

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

bool ResourceEmulator::hasAvailableCPU()
{
	for (int i = 0; i < MAX_CPU_CORES; i++)
	{
		if(this->workingCores[i]->isAvailable())
		{
			return true;
		}
	}

	return false;
}

void ResourceEmulator::onActionFinished(int cpuID)
{
	//reset the working cpu core
	// this->mutex->acquire();
	// this->numWorkingCores--;
	// this->mutex->release();
}

ResourceEmulator::ResourceEmulator()
{
	for(int i = 0; i < MAX_CPU_CORES; i++)
	{
		this->workingCores[i] = std::make_shared<CPUWorker>(i);
	}
	this->mutex = std::make_shared<IETSemaphore>(1);
}

std::shared_ptr<CPUWorker> ResourceEmulator::findFirstAvailableCPU()
{
	for (int i = 0; i < MAX_CPU_CORES; i++)
	{
		if(this->workingCores[i]->isAvailable())
		{
			return this->workingCores[i];
		}
	}

	std::cerr << "No available CPU found." << std::endl;
	return nullptr;
}

CPUWorker::CPUWorker(int cpuID)
{
	this->cpuID = cpuID;
}

void CPUWorker::assignExecutable(Process* process, IActionFinished* actionFinished, int quantumTimes)
{
	this->process = process;
	this->actionFinished = actionFinished;
	this->quantumTimes = quantumTimes;
	this->available = false;
}

void CPUWorker::run()
{
	this->running = true;

	while(this->running)
	{
		//cpu start
		if(this->available == false)
		{
			for (int i = 0; i < this->quantumTimes; i++)
			{
				if (this->process->getRemainingTime() > 0)
				{
					this->process->executeCurrentCommand();
					this->process->moveToNextLine();
				}
				else
				{
					this->available = true;
					this->process = nullptr;
					break;
				}
			}
		}
		else
		{
			//std::cout << "CPU idle: " << this->cpuID << std::endl;
		}
	}
	
	
	//cpu end
	this->actionFinished->onActionFinished(this->cpuID);
}

void CPUWorker::stop()
{
	this->running = false;
}

bool CPUWorker::isAvailable() const
{
	return this->running && this->available;
}
