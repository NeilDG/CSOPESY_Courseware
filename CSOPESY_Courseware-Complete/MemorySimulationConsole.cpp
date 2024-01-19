#include "MemorySimulationConsole.h"
#include <iostream>
#include <ostream>
#include "ConsoleManager.h"
#include "DebugScheduler.h"
#include "FCFSScheduler.h"
#include "FlatMemoryAllocator.h"
#include "MemoryManager.h"
#include "GlobalConfig.h"

MemorySimulationConsole::MemorySimulationConsole() : AConsole(MEMORY_CONSOLE)
{
    if (SchedulerType::SCHEDULER_TYPE == 1)
    {
        this->scheduler = std::make_shared<FCFSScheduler>();
    }
    else
    {
        this->scheduler = std::make_shared<DebugScheduler>();
    }

    // this->scheduler->test_storeRandomProcessesInQueue(50);

    if(MemoryAllocatorType::MEMORY_ALLOCATOR_TYPE == 1)
    {
        this->memoryAllocator = std::make_shared<FlatMemoryAllocator>(MemoryAllocatorType::MAXIMUM_MEMORY_SIZE);
    }
    else
    {
        this->memoryAllocator = nullptr;
    }
}

void MemorySimulationConsole::onEnabled()
{
}

void MemorySimulationConsole::display()
{
}

void MemorySimulationConsole::process()
{
    MemoryManager* memoryManager = MemoryManager::getInstance();
    if (this->printHeader) {
        std::cout << "***************************************************************************************************" << std::endl;
        std::cout << "* Displaying a memory management console!                                                         *" << std::endl;
        std::cout << "* Using scheduler : " << this->getName() << " Using memory emulation: " << memoryManager->getMemoryAllocatorName() << std::endl;
        std::cout << "***************************************************************************************************" << std::endl;

        this->printHeader = false;
    }

    std::cout << "Enter command: ";
    String command;
    std::getline(std::cin, command);

    if (command == "csopesy-smi" || command == "nvidia-smi")
    {
        this->test_mockupUI();
    }
    else if (command == "clear") {
        system("cls");  // Clear screen if 'clear' is entered
        this->printHeader = true;
    }
    else if (command == "exit")
    {
        ConsoleManager::getInstance()->returnToPreviousConsole();
    }
    else
    {
        std::cout << "Unrecognized command: " << command << std::endl;
    }
}

void MemorySimulationConsole::printHeaderBorder() const
{
    const int width = Console::WIDTH - 2;
    std::cout << "+";
    for (int i = 0; i < width; i++)
    {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;
}

void MemorySimulationConsole::test_mockupUI()
{
    const int width = Console::WIDTH - 2;
    
    this->printHeaderBorder();
    std::cout << " CSOPESY-SMI V001.000.00       Driver Version: 999.999.99       CUDA Version: 11.2" << std::endl;

    this->printHeaderBorder();

    //print memory usage / utility usage header
    int memoryDisplayWidth = 32;
    std::cout << "|";
    for (int i = 0; i < memoryDisplayWidth / 2; i++)
    {
        std::cout << " ";
    }

    std::cout << "Memory Usage";

    for (int i = 0; i < memoryDisplayWidth / 2; i++)
    {
        std::cout << " ";
    }

    std::cout << "|";

    std::cout << "|";
    for (int i = 0; i < memoryDisplayWidth / 2; i++)
    {
        std::cout << " ";
    }

    std::cout << "Memory Utilization";

    for (int i = 0; i < memoryDisplayWidth / 2; i++)
    {
        std::cout << " ";
    }

    std::cout << "|" << std::endl;

    //print memory usage / utility metrics
    memoryDisplayWidth = 24;
    std::cout << "|";
    for (int i = 0; i < memoryDisplayWidth / 2; i++)
    {
        std::cout << " ";
    }

    std::cout << "00000 MB / 240000 MB";

    for (int i = 0; i < memoryDisplayWidth / 2; i++)
    {
        std::cout << " ";
    }

    std::cout << "|";

    memoryDisplayWidth = 46;

    std::cout << "|";
    for (int i = 0; i < memoryDisplayWidth / 2; i++)
    {
        std::cout << " ";
    }

    std::cout << "100%";

    for (int i = 0; i < memoryDisplayWidth / 2; i++)
    {
        std::cout << " ";
    }

    std::cout << "|" << std::endl;

    std::cout << std::endl << std::endl;
    this->printHeaderBorder();

    std::cout << "|";
    std::cout << " Processes:" << std::endl;

    int displayWidth = (width - 8) / 4;
    std::cout << "| ";

    std::cout << "CPU #";
    for(int i = 0; i < displayWidth - 8; i++)
    {
        std::cout << " ";
    }

    std::cout << "PID";
    for (int i = 0; i < displayWidth - 8; i++)
    {
        std::cout << " ";
    }

    std::cout << "Process Name";
    for (int i = 0; i < displayWidth + 16; i++)
    {
        std::cout << " ";
    }

    std::cout << "Memory Usage";
    std::cout << std::endl;

    std::cout << "|";
    for (int i = 0; i < width; i++)
    {
        std::cout << "=";
    }
    std::cout << "|" << std::endl;

}
