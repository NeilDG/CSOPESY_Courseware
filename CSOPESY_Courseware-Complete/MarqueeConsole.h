#pragma once
#include <sstream>
#include "AConsole.h"
class MarqueeConsole :    public AConsole
{
public:
	MarqueeConsole();
	void display() override;
	bool processCommand() override;

private:
	int x, y;  // Position
	int dx, dy;  // Direction
	const String HELLO_WORLD_STRING = "Hello world in marquee!";

	int screenWidth = 120;
	int screenHeight = 25;
	const int REFRESH_DELAY = 10; //change this value to slow/increase refresh rate of marquee

	void move();
	void setCursorPosition(int posX, int posY) const;
	bool isKeyPressed() const;
	char getPressedKey() const;

	String currentCommand;
	bool commandEntered = false;

	std::stringstream outputBuffer;
};

