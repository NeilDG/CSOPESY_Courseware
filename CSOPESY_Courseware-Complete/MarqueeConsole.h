#pragma once
#include "AConsole.h"
class MarqueeConsole :    public AConsole
{
public:
	MarqueeConsole();
	void display() override;
	bool processCommand() override;
};

