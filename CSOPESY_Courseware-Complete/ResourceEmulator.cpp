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

CPUWorker::CPUWorker(std::shared_ptr<IExecutableAction> executableAction)
{
	this->executableAction = executableAction;
}

void CPUWorker::run()
{
	this->executableAction->execute();
}
