#pragma once
#include <sstream>
#include "AConsole.h"
#include "DebugScheduler.h"

class SchedulingConsole :    public AConsole
{
public:
	SchedulingConsole();
	void onEnabled() override;
	void display() override;
	void process() override;

private:
	std::shared_ptr<AScheduler> scheduler;
	std::unique_ptr<AConsole> chosenConsole;
};

class Scheduling_UIVersion1 : public AConsole
{
public:
	Scheduling_UIVersion1(std::shared_ptr<AScheduler> scheduler);
	void onEnabled() override;
	void display() override;
	void process() override;

private:
	std::shared_ptr<AScheduler> scheduler;
	String currentCommand;
	bool commandEntered = false;

	//display buffers information
	int messageRow;
	std::stringstream outputBuffer;

	String btmCommandDisplay;
	int btmCommandPosition;

	friend class SchedulingConsole;
};

class Scheduling_UIVersion2 : public AConsole
{
public:
	Scheduling_UIVersion2(std::shared_ptr<AScheduler> scheduler);
	void onEnabled() override;
	void display() override;
	void process() override;

private:
	std::shared_ptr<AScheduler> scheduler;
	struct UIVersion2Flags
	{
		bool schedulerRunning;
		bool printHeader;
	};
	UIVersion2Flags ui2flags;
};

