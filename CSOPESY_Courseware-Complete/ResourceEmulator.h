#pragma once
#include <unordered_map>
#include "IETThread.h"
#include "Process.h"
#include "IETSemaphore.h"

class CPUWorker;
class IActionFinished
{
public:
	virtual void onActionFinished(int cpuID) = 0;
};

/**
 * \brief A class that emulates resources such as CPU and available memory.
 */
static const int MAX_CPU_CORES = 1;
class ResourceEmulator : public IActionFinished
{
public:
	static ResourceEmulator* getInstance();
	static void initialize();
	static void destroy();

	//One cpu core = one thread
	typedef std::unordered_map<int, std::shared_ptr<CPUWorker>> CPUCoreGroup;
	bool scheduleCPUWork(std::shared_ptr<Process> process);
	bool hasAvailableCPU() const;
	void onActionFinished(int cpuID) override;

private:
	ResourceEmulator();
	~ResourceEmulator() = default;
	ResourceEmulator(ResourceEmulator const&) {}; // copy constructor is private
	ResourceEmulator& operator=(ResourceEmulator const&) {}; // assignment operator is private*/
	static ResourceEmulator* sharedInstance;

	int numWorkingCores = 0;

	//mutual exclusion semaphore
	std::shared_ptr<IETSemaphore> mutex;
};

class CPUWorker
{
public:
	CPUWorker(int cpuID);
	void assignExecutable(std::shared_ptr<Process> process, IActionFinished* actionFinished, int quantumTimes = 100000);
	void run();
	int getID();

private:
	int cpuID;
	int quantumTimes = 1;
	std::shared_ptr<Process> process;
	IActionFinished* actionFinished;

	friend class ResourceEmulator;
};

