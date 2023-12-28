#pragma once
#include <sstream>
#include "AConsole.h"
#include "MarqueeWorkerThread.h"

class MarqueeConsole :    public AConsole
{
public:
	MarqueeConsole();
	void display() override;
	bool processCommand() override;

private:
	// int x, y;  // Position
	// int dx, dy;  // Direction
	// const String HELLO_WORLD_STRING = "Hello world in marquee!";

	int screenWidth = 120;
	int screenHeight = 25;
	const int REFRESH_DELAY = 50; //change this value to slow/increase refresh rate of marquee
	const int POLLING_DELAY = 1; //change this value to slow/increase polling rate

	// void move();
	bool isKeyPressed() const;
	char getPressedKey() const;

	String currentCommand;
	bool commandEntered = false;

	std::stringstream outputBuffer;

	std::unique_ptr<MarqueeWorkerThread> marqueeWorker;
	bool marqueeWorkerStarted = false;
};

