#include "GlobalScheduler.h"

#include "DebugScheduler.h"
#include "FCFSScheduler.h"

GlobalScheduler* GlobalScheduler::sharedInstance = nullptr;
GlobalScheduler* GlobalScheduler::getInstance()
{
	return sharedInstance;
}

void GlobalScheduler::initialize()
{
	sharedInstance = new GlobalScheduler();
}

void GlobalScheduler::destroy()
{
	delete sharedInstance;
}

void GlobalScheduler::tick() const
{
	this->scheduler->execute();
}

/**
 * \brief Creates a new process (if none exists). If a process with the same name exists, it returns the existing process.
 * \param name 
 * \return 
 */
std::shared_ptr<Process> GlobalScheduler::createUniqueProcess(String name)
{
	std::shared_ptr<Process> existingProcess = this->findProcess(name);
	if(existingProcess != nullptr)
	{
		return existingProcess;
	}
	else
	{
		Process::RequirementFlags reqFlags = { ProcessRequirementFlags_CONFIG::REQUIRE_FILES, ProcessRequirementFlags_CONFIG::NUM_FILES,
		ProcessRequirementFlags_CONFIG::REQUIRE_MEMORY, ProcessRequirementFlags_CONFIG::MEMORY_REQUIRED };

		if (name == "")
		{
			name = this->generateProcessName();

		}
		std::shared_ptr<Process> newProcess = std::make_shared<Process>(this->pidCounter, name, reqFlags);
		newProcess->test_generateRandomCommands(50);

		//put new process to ready queue
		this->scheduler->addProcess(newProcess);
		this->pidCounter++;

		return newProcess;
	}
	
}

std::shared_ptr<Process> GlobalScheduler::findProcess(String name) const
{
	std::shared_ptr<Process> existingProcess = this->scheduler->findProcess(name);
	if (existingProcess != nullptr)
	{
		return existingProcess;
	}
	else
	{
		return nullptr;
	}
}

/**
 * \brief Generates a process name based on the current pid counter
 * \return 
 */
String GlobalScheduler::generateProcessName()
{
	String name = "process_" + std::to_string(sharedInstance->pidCounter);
	return name;
}

String GlobalScheduler::generateReport() const
{
	std::vector<AScheduler::ProcessInfo> runningList = this->scheduler->getRunningProcessInfo();
	std::stringstream ss;

	ss << String("CPU Utilization: 100%") << std::endl;
	ss << String("Cores used: 0") << std::endl;
	ss << String("Cores available: 4") << std::endl;

	ss << String("--------------------------------------") << std::endl;
	ss << String("Running processes:") << std::endl;
	for(int i = 0; i < runningList.size(); i++)
	{
		ss << String("Name: ") << runningList[i].name << String(" | ");
		if(runningList[i].cpuID < 0) //no core/isn't scheduled yet
		{
			ss << String("Core: N/A") << String(" | ");
		}
		else
		{
			ss << String("Core: ") << std::to_string(runningList[i].cpuID) << String(" | ");
		}
		
		ss << std::to_string(runningList[i].lineCounter) << String(" / ") << runningList[i].linesOfCode << String(" | ");
		ss << String("\n");
	}

	ss << String("\n");


	ss << String("Finished processes:") << std::endl;
	ss << String("\n");
	ss << String("--------------------------------------") << std::endl;

	return ss.str();
}

void GlobalScheduler::test_createRandomProcesses(int limit)
{
	for (int i = 0; i < limit; i++)
	{
		this->createUniqueProcess();
	}
}

GlobalScheduler::GlobalScheduler()
{
	if(SchedulerType::SCHEDULER_TYPE == 1)
	{
		this->scheduler = std::make_unique<FCFSScheduler>();
	}
	else
	{
		this->scheduler = std::make_unique<DebugScheduler>();
	}
}
