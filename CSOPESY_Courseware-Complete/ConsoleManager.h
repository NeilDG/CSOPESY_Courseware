#pragma once
#include <memory>
#include <vector>

#include "AConsole.h"
#include <unordered_map>
#include <Windows.h>

typedef std::string String;
const String MAIN_CONSOLE = "MAIN_CONSOLE";
const String MARQUEE_CONSOLE = "MARQUEE_CONSOLE";

class ConsoleManager
{
public:
	typedef std::unordered_map<String, std::shared_ptr<AConsole>> ConsoleTable;

	static ConsoleManager* getInstance();
	static void initialize();
	static void destroy();

	bool drawConsole() const;
	void switchConsole(String consoleName);
	void returnToPreviousConsole();

	HANDLE getConsoleHandle() const;

private:
	ConsoleManager();
	~ConsoleManager() = default;
	ConsoleManager(ConsoleManager const&) {}; // copy constructor is private
	ConsoleManager& operator=(ConsoleManager const&) {}; // assignment operator is private*/
	static ConsoleManager* sharedInstance;

	ConsoleTable consoleTable;
	std::shared_ptr<AConsole> currentConsole;
	std::shared_ptr<AConsole> previousConsole;

	HANDLE consoleHandle;

	
};

