#pragma once
#include <queue>

#include "IETThread.h"
#include "Process.h"
#include "TypedefRepo.h"

static const String DEBUG_SCHEDULER_NAME = "DebugScheduler";
static const String FCFS_SCHEDULER_NAME = "FCFSScheduler";
static const String SJF_NOPREEMPT_SCHEDULER_NAME = "SJF-NoPreempt-Scheduler";
static const String SJF_PREEMPT_SCHEDULER_NAME = "SJF-Preempt-Scheduler";

class AScheduler : public IETThread
{
public:
	enum SchedulingAlgorithm
	{
		DEBUG,
		FCFS,
		SHORTEST_JOB_FIRST_NONPREEMPTIVE,
		SHORTEST_JOB_FIRST_PREEMPTIVE,
		ROUND_ROBIN
	};

	AScheduler(SchedulingAlgorithm schedulingAlgo, int pid, String processName);

	void run() override;
	void stop();
	virtual void execute() = 0;

	struct ProcessTimeInfo
	{
		int pid;
		int remainingTime;
	};

	std::vector<ProcessTimeInfo> getAllProcessRemainingTime() const;

	//test functions
	void test_storeRandomProcessesInQueue(int limit);

protected:
	typedef std::queue<std::shared_ptr<Process>> ProcessQueue;
	typedef std::vector<std::shared_ptr<Process>> ProcessList;
	ProcessQueue processQueue;
	ProcessList processList;

private:
	SchedulingAlgorithm schedulingAlgo;
	int pid;
	String processName;

	bool running = true;
};

