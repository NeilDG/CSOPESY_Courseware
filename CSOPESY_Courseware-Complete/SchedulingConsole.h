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
	std::unique_ptr<DebugScheduler> debugScheduler;

	String currentCommand;
	bool commandEntered = false;

	//display buffers information
	int messageRow;
	std::stringstream outputBuffer;

	String btmCommandDisplay;
	int btmCommandPosition;
	
};

