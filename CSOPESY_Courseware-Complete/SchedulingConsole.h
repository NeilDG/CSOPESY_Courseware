#pragma once
#include <sstream>
#include "AConsole.h"
#include "DebugScheduler.h"

class SchedulingConsole :    public AConsole
{
public:
	SchedulingConsole();
	void display() override;
	bool processCommand() override;

private:
	String currentCommand;
	bool commandEntered = false;

	//display buffers information
	int messageRow;
	std::stringstream outputBuffer;

	std::unique_ptr<DebugScheduler> debugScheduler;
};

