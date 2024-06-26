#pragma once
#include <queue>
#include <sstream>
#include <unordered_map>

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

	void addProcess(std::shared_ptr<Process> process);
	std::shared_ptr<Process> findProcess(String processName);
	void run() override;
	void stop();

	virtual void init() = 0;
	virtual void execute() = 0;

	struct ProcessInfo
	{
		int pid;
		String name;
		int cpuID;
		int lineCounter;
		int linesOfCode;
		int remainingTime;
	};

	std::vector<ProcessInfo> getAllProcessRemainingTime() const;
	std::vector<ProcessInfo> getRunningProcessInfo() const;
	String getName();
	String getLatestMsg();

protected:
	typedef std::queue<std::shared_ptr<Process>> ProcessQueue;
	typedef std::vector<std::shared_ptr<Process>> ProcessList;
	typedef std::unordered_map<String, std::shared_ptr<Process>> ProcessMap;
	ProcessQueue readyQueue;
	ProcessList processList;
	ProcessMap processMap;

	std::stringstream outputBuffer;

private:
	SchedulingAlgorithm schedulingAlgo;
	int pid;
	String processName;

	bool running = true;
};

