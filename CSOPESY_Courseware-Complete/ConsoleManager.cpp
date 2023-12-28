#include "ConsoleManager.h"

#include <iostream>

#include "MainConsole.h"
#include "MarqueeConsole.h"

ConsoleManager* ConsoleManager::sharedInstance = nullptr;
ConsoleManager* ConsoleManager::getInstance()
{
	return sharedInstance;
}

void ConsoleManager::initialize()
{
	sharedInstance = new ConsoleManager();
}

void ConsoleManager::destroy()
{
	delete sharedInstance;
}

bool ConsoleManager::drawConsole() const
{
	if(this->currentConsole != nullptr)
	{
		this->currentConsole->display();
		return this->currentConsole->processCommand();
	}
	else
	{
		std::cerr << "There is no assigned console. Please check." << std::endl;
		return true;
	}
}

void ConsoleManager::switchConsole(String consoleName)
{
	if(this->consoleTable.contains(consoleName))
	{
		// Clear the screen
		system("cls");
		this->previousConsole = this->currentConsole;
		this->currentConsole = this->consoleTable[consoleName];
	}
	else
	{
		std::cerr << "Console name " << consoleName << " not found. Was it initialized?" << std::endl;
	}
}

ConsoleManager::ConsoleManager()
{
	//initialize consoles
	this->consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	const std::shared_ptr<MainConsole> mainConsole = std::make_shared<MainConsole>();
	const std::shared_ptr<MarqueeConsole> marqueeConsole = std::make_shared<MarqueeConsole>();

	this->consoleTable[MAIN_CONSOLE] = mainConsole;
	this->consoleTable[MARQUEE_CONSOLE] = marqueeConsole;

	this->switchConsole(MAIN_CONSOLE);

	//initialize mutex
	this->mutex = std::make_unique<IETSemaphore>(1);

}

void ConsoleManager::returnToPreviousConsole()
{
	if(this->previousConsole != nullptr)
	{
		// Clear the screen
		system("cls");
		this->currentConsole = this->previousConsole;
	}
}

HANDLE ConsoleManager::getConsoleHandle() const
{
	return this->consoleHandle;
}

void ConsoleManager::setCursorPosition(int posX, int posY) const
{
	// this->mutex->acquire();

	COORD coord;
	coord.X = posX;
	coord.Y = posY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	// this->mutex->release();
}
