#pragma once
#include <sstream>
#include "AConsole.h"
#include "MarqueeWorkerThread.h"

class MarqueeConsole :    public AConsole
{
public:
	MarqueeConsole();
	void onEnabled() override;
	void display() override;
	void process() override;

private:
	const int REFRESH_DELAY = 50; //change this value to slow/increase refresh rate of marquee
	const int POLLING_DELAY = 1; //change this value to slow/increase polling rate

	String currentCommand;
	bool commandEntered = false;
	std::stringstream outputBuffer;

	std::unique_ptr<MarqueeWorkerThread> marqueeWorker;
	bool marqueeWorkerStarted = false;
};

