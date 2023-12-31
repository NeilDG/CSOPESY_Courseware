#pragma once
#include <unordered_map>

#include "IETThread.h"
class IExecutableAction;
class CPUWorker;
class IActionFinished
{
public:
	virtual void onActionFinished(int cpuID) = 0;
};

/**
 * \brief A class that emulates resources such as CPU and available memory.
 */
static const int MAX_CPU_CORES = 2;
class ResourceEmulator : public IActionFinished
{
public:
	static ResourceEmulator* getInstance();
	static void initialize();
	static void destroy();

	//One cpu core = one thread
	typedef std::unordered_map<int, std::shared_ptr<CPUWorker>> CPUCoreGroup;
	bool scheduleCPUWork(IExecutableAction* executableAction);
	void onActionFinished(int cpuID) override;

private:
	ResourceEmulator();
	~ResourceEmulator() = default;
	ResourceEmulator(ResourceEmulator const&) {}; // copy constructor is private
	ResourceEmulator& operator=(ResourceEmulator const&) {}; // assignment operator is private*/
	static ResourceEmulator* sharedInstance;

	CPUCoreGroup workingCores;
};

class CPUWorker: public IETThread
{
public:
	CPUWorker(int cpuID);
	void assignExecutable(IExecutableAction* executableAction, IActionFinished* actionFinished);
	void run() override;
	bool isAvailable() const;
	int getID();

private:
	int cpuID;
	bool available = true;
	IExecutableAction* executableAction;
	IActionFinished* actionFinished;
};

class IExecutableAction
{
public:
	virtual void executeAction() = 0;
};

