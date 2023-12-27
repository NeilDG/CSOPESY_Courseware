#include "MarqueeConsole.h"

#include <iostream>

#include "ConsoleManager.h"

MarqueeConsole::MarqueeConsole() : AConsole("MARQUEE_CONSOLE")
{
}

void MarqueeConsole::display()
{
    std::cout << "*****************************************" << std::endl;
    std::cout << "* Displaying a marquee console! *" << std::endl;
    std::cout << "*****************************************" << std::endl;
}

bool MarqueeConsole::processCommand()
{
    std::string command;
    std::cout << "Enter a command for " << this->name << ": ";
    std::cin >> command;
    std::cout << "Command processed in " << this->name << ": " << command << std::endl;

    if(command == "exit")
    {
        ConsoleManager::getInstance()->returnToPreviousConsole();
    }

    return false;
}
