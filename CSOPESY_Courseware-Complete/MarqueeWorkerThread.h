#pragma once
#include "IETThread.h"
#include "TypedefRepo.h"

class MarqueeWorkerThread :    public IETThread
{
public:
	MarqueeWorkerThread(int screenWidth, int screenHeight, int refreshDelay);
	void run() override;

	void dismiss();
	void renderCurrentState() const;

private:
	bool isRunning = true;
	int x, y;  // Position
	int dx, dy;  // Direction
	const String HELLO_WORLD_STRING = "Hello world in marquee!";

	int screenWidth;
	int screenHeight;
	int refreshDelay;

	void process();
	void move();
};

