// CSOPESY_Courseware-Complete.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <Windows.h>
#include <io.h>

#include "FileSystem.h"

//columns x rows
void SetConsoleWindowSize(int width, int height) {
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const COORD newSize = { static_cast<short>(width), static_cast<short>(height) };
    SetConsoleScreenBufferSize(hConsole, newSize);

	const SMALL_RECT rect = { 0, 0, newSize.X - 1, newSize.Y - 1 };
    SetConsoleWindowInfo(hConsole, TRUE, &rect);
}

void DisplayCSOPESY(HANDLE consoleHandle) {
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

// void CreateNewConsole(const std::string& command) {
//     // Allocate a new console for the application
//     AllocConsole();
//
//     // Open CONOUT$ for writing to the new console
//     FILE* newStdout;
//     freopen_s(&newStdout, "CONOUT$", "w", stdout);
//
//     // Duplicate file descriptors to redirect standard input and error
//     _dup2(_fileno(newStdout), _fileno(stdout));
//     _dup2(_fileno(newStdout), _fileno(stderr));
//
//     // Free the console when the application is done
//     FreeConsole();
// }

int main()
{
    FileSystem::initialize();
    FileSystem::getInstance()->test_createRandomFiles(100);
    FileSystem::getInstance()->saveFileSystem();
    // FileSystem::getInstance()->loadFileSystem();

    //console proper
    const HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    // Clear the screen
    system("cls");

    // SetConsoleWindowSize(80, 25);
    DisplayCSOPESY(consoleHandle);

    if(consoleHandle == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error getting console handle \n";
        return -1;
    }
    
    // Reset console text attributes (optional) - evaluates to a (1, 1, 1) = white color
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    // Main loop
    while (true) {
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
            break;
        }
        else if (command == "clear" || command == "cls") {
            // Clear the screen
            system("cls");
            // Redisplay "CSOPESY" ASCII art after clearing
            DisplayCSOPESY(consoleHandle);

            // Reset console text attributes (optional) - evaluates to a (1, 1, 1) = white color
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        else if (command.substr(0, 5) == "mkdir")
        {
            if(command.length() > 6)
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
        else if(command == "dirlist")
        {
            FileSystem::getInstance()->printAllDirectories(true);
        }
        else {
            // Simulate command execution
            std::cout << "Executing command: " << command << std::endl;
        }
    }

    return 0;
}
