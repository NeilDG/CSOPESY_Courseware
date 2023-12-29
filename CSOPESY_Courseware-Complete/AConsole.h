#pragma once
#include <string>

class AConsole
{
public:
	typedef std::string String;
	AConsole(String name);
	~AConsole() = default;

	String getName();
	virtual void display() = 0;
	virtual bool processCommand() = 0;

	String name;
	friend class ConsoleManager;

	static bool isKeyPressed();
	static char getPressedKey();
};

