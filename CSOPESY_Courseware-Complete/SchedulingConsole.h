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
	void displayUI_Version1();
	void displayUI_Version2();

	std::unique_ptr<DebugScheduler> debugScheduler;

	String currentCommand;
	bool commandEntered = false;

	//display buffers information
	int messageRow;
	std::stringstream outputBuffer;

	String btmCommandDisplay;
	int btmCommandPosition;

	struct UIVersion2Flags
	{
		bool schedulerRunning;
		bool printHeader;
	};
	UIVersion2Flags ui2flags;
	
};

