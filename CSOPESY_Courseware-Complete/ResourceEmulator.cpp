#include "ResourceEmulator.h"

CPUWorker::CPUWorker(std::shared_ptr<IExecutableAction> executableAction)
{
	this->executableAction = executableAction;
}

void CPUWorker::run()
{
	this->executableAction->execute();
}
