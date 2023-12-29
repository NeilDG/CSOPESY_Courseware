// CSOPESY_Courseware-Complete.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <Windows.h>
#include <io.h>
#include <tchar.h>

#include "ConsoleManager.h"
#include "FileSystem.h"
#include "InputManager.h"

//columns x rows
void SetConsoleWindowSize(int width, int height) {
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const COORD newSize = { static_cast<short>(width), static_cast<short>(height) };
    SetConsoleScreenBufferSize(hConsole, newSize);

	const SMALL_RECT rect = { 0, 0, newSize.X - 1, newSize.Y - 1 };
    SetConsoleWindowInfo(hConsole, TRUE, &rect);
}

int main()
{
    InputManager::initialize();
    FileSystem::initialize();
    // FileSystem::getInstance()->test_createRandomFiles(1000);
    // FileSystem::getInstance()->saveFileSystem();
    FileSystem::getInstance()->loadFileSystem();
    ConsoleManager::initialize();
    
    bool running = true;
    while(running)
    {
        ConsoleManager::getInstance()->process();
        ConsoleManager::getInstance()->drawConsole();

        running = ConsoleManager::getInstance()->isRunning();
    }

    ConsoleManager::destroy();
    InputManager::destroy();
    return 0;
}
