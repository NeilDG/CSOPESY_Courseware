#include <iostream>
#include <ostream>
#include "MainConsole.h"
#include "ConsoleManager.h"
#include "FileSystem.h"

MainConsole::MainConsole() : AConsole(MAIN_CONSOLE)
{
}

void MainConsole::DisplayCSOPESY() const
{
    HANDLE consoleHandle = ConsoleManager::getInstance()->getConsoleHandle();
    // Display "CSOPESY" ASCII art in the upper portion of the console
    std::cout << "   ____ ____   ___  ____  _____ ______   __                             \n";
    std::cout << "  / ___/ ___| / _ \|  _ \| ____/ ___\ \ / /                             \n";
    std::cout << " | |   \___ \| | | | |_) |  _| \___ \\ V /                              \n";
    std::cout << " | |___ ___) | |_| |  __/| |___ ___) || |                               \n";
    std::cout << "  \____|____/ \___/|_|   |_____|____/ |_|        _      _ _             \n";


    // Output to the console
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::cout << "Hello, Welcome to CSOPESY commandline!\n";

    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    std::cout << "Type 'exit' to quit, 'clear' to clear the screen " << std::endl;
}

void MainConsole::display()
{
	this->DisplayCSOPESY();

	HANDLE consoleHandle = ConsoleManager::getInstance()->getConsoleHandle();
	// Reset console text attributes (optional) - evaluates to a (1, 1, 1) = white color
	SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

bool MainConsole::processCommand()
{
    HANDLE consoleHandle = ConsoleManager::getInstance()->getConsoleHandle();
    
    // Position the cursor at the bottom for user input
    // const COORD bottomPosition = { 0, 24 };
    // SetConsoleCursorPosition(consoleHandle, bottomPosition);

    // Display prompt
    std::cout << "Enter a command: ";

    // Read user input
    std::string command;
    std::getline(std::cin, command);

    // Check for exit condition
    if (command == "exit") {
        return true;
    }

    if (command == "clear" || command == "cls") {
        // Clear the screen
        system("cls");

        // Reset console text attributes (optional) - evaluates to a (1, 1, 1) = white color
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else if (command.substr(0, 5) == "mkdir")
    {
        if (command.length() > 6)
        {
            std::string directoryPath = command.substr(6);
            if (!directoryPath.empty())
            {
                std::cout << "Make directory command recognized. Proposed path: " << directoryPath << std::endl;
            }
            else
            {
                std::cerr << "Invalid mkdir command. Usage: mkdir <directory>" << std::endl;
            }
        }
        else
        {
            std::cerr << "Invalid mkdir command. Usage: mkdir <directory>" << std::endl;
        }

    }
    else if (command == "marquee")
    {
        ConsoleManager::getInstance()->switchConsole(MARQUEE_CONSOLE);
    }
    else if (command == "dirlist")
    {
        FileSystem::getInstance()->printAllDirectories(true);
    }
    else {
        // Simulate command execution
        std::cout << "Executing command: " << command << std::endl;
    }

    return false;
    
}
