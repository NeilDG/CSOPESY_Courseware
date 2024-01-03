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
#include "MemoryManager.h"
#include "MessageBuffer.h"
#include "ResourceEmulator.h"

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
    MessageBuffer::initialize();
    ResourceEmulator::initialize();
    MemoryManager::initialize();
    
    // bool running = true;
    // while(running)
    // {
    //     ConsoleManager::getInstance()->process();
    //     ConsoleManager::getInstance()->drawConsole();
    //
    //     running = ConsoleManager::getInstance()->isRunning();
    // }

    // Allocate memory
    MemoryManager* memoryManager = MemoryManager::getInstance();

    void* ptr1 = memoryManager->allocate(64);
    void* ptr2 = memoryManager->allocate(64);

    // Visualize memory
    std::cout << memoryManager->visualizeMemory();
    //
    // Deallocate memory
    memoryManager->deallocate(ptr1, 32);
    memoryManager->deallocate(ptr2, 32);
    
    // Visualize memory after deallocation
    std::cout << memoryManager->visualizeMemory();

    MemoryManager::destroy();
    ResourceEmulator::destroy();
    MessageBuffer::destroy();
    ConsoleManager::destroy();
    InputManager::destroy();
    return 0;
}
