#pragma once
#include <sstream>
#include "AConsole.h"

class SchedulingConsole :    public AConsole
{
public:
	SchedulingConsole();
	void display() override;
	bool processCommand() override;

private:
	String currentCommand;
	bool commandEntered = false;
	std::stringstream outputBuffer;
};

