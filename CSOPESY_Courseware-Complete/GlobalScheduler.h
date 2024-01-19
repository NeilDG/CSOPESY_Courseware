#pragma once
#include "AScheduler.h"
/**
 * \brief The global scheduler for the CSOPESY-emulator. References an AScheduler instance.
 */
class GlobalScheduler
{
public:
	static GlobalScheduler* getInstance();
	static void initialize();
	static void destroy();

	void tick() const;

	std::shared_ptr<Process> createUniqueProcess(String name = "");
	std::shared_ptr<Process> findProcess(String name) const;
	static String generateProcessName();

	static String generateReport();

	void test_createRandomProcesses(int limit);

private:
	GlobalScheduler();
	~GlobalScheduler() = default;
	GlobalScheduler(GlobalScheduler const&) {}; // copy constructor is private
	GlobalScheduler& operator=(GlobalScheduler const&) {}; // assignment operator is private*/
	static GlobalScheduler* sharedInstance;

	std::unique_ptr<AScheduler> scheduler;

	int pidCounter = 0;
};

