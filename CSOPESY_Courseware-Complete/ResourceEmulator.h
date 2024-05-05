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
class ResourceEmulator : public IActionFinished
{
public:
	static ResourceEmulator* getInstance();
	static void initialize();
	static void destroy();

	//One cpu core = one thread
	typedef std::unordered_map<int, std::shared_ptr<CPUWorker>> CPUCoreGroup;
	void startAllCPUs();
	bool scheduleCPUWork(std::shared_ptr<Process> process);
	bool hasAvailableCPU();
	void onActionFinished(int cpuID) override;

private:
	ResourceEmulator();
	~ResourceEmulator() = default;
	ResourceEmulator(ResourceEmulator const&) {}; // copy constructor is private
	ResourceEmulator& operator=(ResourceEmulator const&) {}; // assignment operator is private*/
	static ResourceEmulator* sharedInstance;

	std::shared_ptr<CPUWorker> findFirstAvailableCPU();

	CPUCoreGroup workingCores;
	//mutual exclusion semaphore
	std::shared_ptr<IETSemaphore> mutex;
};

class CPUWorker : public IETThread
{
public:
	CPUWorker(int cpuID);
	void assignExecutable(Process* process, IActionFinished* actionFinished, int quantumTimes = 100000);
	void run() override;
	void stop();
	int getID();
	bool isAvailable() const;

private:
	int cpuID;
	int quantumTimes = 1;
	bool running = false;
	bool available = true;
	Process* process;
	IActionFinished* actionFinished;

	friend class ResourceEmulator;
};

