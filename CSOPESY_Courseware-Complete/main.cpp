// CSOPESY_Courseware-Complete.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <Windows.h>
#include <io.h>
#include <tchar.h>

#include "ConsoleManager.h"
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

int main()
{
    FileSystem::initialize();
    // FileSystem::getInstance()->test_createRandomFiles(1000);
    // FileSystem::getInstance()->saveFileSystem();
    FileSystem::getInstance()->loadFileSystem();
    ConsoleManager::initialize();
    
    bool running = true;
    while(running)
    {
        running = !ConsoleManager::getInstance()->drawConsole();
    }

    return 0;
}
