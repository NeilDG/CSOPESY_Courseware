#include "MarqueeConsole.h"
#include <conio.h>  // For _kbhit() and _getch()
#include <iostream>
#include "ConsoleManager.h"
#include "IETThread.h"

MarqueeConsole::MarqueeConsole() : AConsole(MARQUEE_CONSOLE)
{
    this->x = 0;
    this->y = 4;
    this->dx = 1;
    this->dy = 1;
}

void MarqueeConsole::display()
{
    system("cls"); // Clear screen
    this->setCursorPosition(0, 0);
    std::cout << "*****************************************" << std::endl;
    std::cout << "* Displaying a marquee console! *" << std::endl;
    std::cout << "*****************************************" << std::endl;

    this->move();
    this->setCursorPosition(x, y);
    std::cout << HELLO_WORLD_STRING;
}

bool MarqueeConsole::processCommand()
{
    this->setCursorPosition(0, this->screenHeight - 1);
    std::cout << "Enter a command for " << this->name << ": " << this->currentCommand;

    if (this->isKeyPressed()) {
        char ch = this->getPressedKey();
        if (ch != '\n' && ch != '\r')
        {
            this->currentCommand.push_back(ch);
            this->commandEntered = false;
        }
        else
        {
            this->commandEntered = true;
        }
    }

    if(this->commandEntered)
    {
        //process commands
        if (this->currentCommand == "exit") {
            ConsoleManager::getInstance()->returnToPreviousConsole();
        }
        else if (this->currentCommand == "clear") {
            this->outputBuffer.str("");
            system("cls");  // Clear screen if 'clear' is entered
        }
        else {
            this->outputBuffer << std::string("Command processed in ") << this->name << ": " << this->currentCommand << std::endl;
        }

        //reset flags
        this->commandEntered = false;
        this->currentCommand = "";
    }

    this->setCursorPosition(0, this->screenHeight);
    std::cout << this->outputBuffer.str();

    this->setCursorPosition(0, this->screenHeight - 1);
    IETThread::sleep(100);

    return false;
}

void MarqueeConsole::move()
{
    x += dx;
    y += dy;

    if (x <= 0 || x >= screenWidth - HELLO_WORLD_STRING.length())
        dx = -dx;

    if (y <= 4 || y >= screenHeight - 2)
        dy = -dy;
}

void MarqueeConsole::setCursorPosition(int posX, int posY) const
{
    COORD coord;
    coord.X = posX;
    coord.Y = posY;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool MarqueeConsole::isKeyPressed() const
{
    return _kbhit() != 0;
}

char MarqueeConsole::getPressedKey() const
{
    return _getch();
}
