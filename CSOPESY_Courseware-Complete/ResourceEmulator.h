#pragma once
#include <vector>
#include "IETThread.h"
class CPUWorker;
class IExecutableAction;

/**
 * \brief A class that emulates resources such as CPU and available memory.
 */
class ResourceEmulator
{
public:
	static ResourceEmulator* getInstance();
	static void initialize();
	static void destroy();

	//One cpu core = one thread
	typedef std::vector<std::shared_ptr<CPUWorker>> CPUCoreGroup;

private:
	ResourceEmulator();
	~ResourceEmulator() = default;
	ResourceEmulator(ResourceEmulator const&) {}; // copy constructor is private
	ResourceEmulator& operator=(ResourceEmulator const&) {}; // assignment operator is private*/
	static ResourceEmulator* sharedInstance;

	CPUCoreGroup cpuCores;
};

class CPUWorker: public IETThread
{
public:
	CPUWorker(std::shared_ptr<IExecutableAction> executableAction);
	void run() override;

private:
	std::shared_ptr<IExecutableAction> executableAction;
};

class IExecutableAction
{
public:
	virtual void execute() = 0;
};

