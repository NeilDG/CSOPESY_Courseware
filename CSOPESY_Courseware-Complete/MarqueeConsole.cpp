#include "MarqueeConsole.h"
#include <iostream>
#include "ConsoleManager.h"
#include "IETThread.h"
#include "GlobalConfig.h"

MarqueeConsole::MarqueeConsole() : AConsole(MARQUEE_CONSOLE)
{
    this->marqueeWorker = std::make_unique<MarqueeWorkerThread>(Console::WIDTH, Console::HEIGHT, this->REFRESH_DELAY);
}

void MarqueeConsole::display()
{
    // system("cls"); // Clear screen
    // this->setCursorPosition(0, 0);
    // std::cout << "*****************************************" << std::endl;
    // std::cout << "* Displaying a marquee console! *" << std::endl;
    // std::cout << "*****************************************" << std::endl;
    //
    // this->move();
    // this->setCursorPosition(x, y);
    // std::cout << HELLO_WORLD_STRING;

    //delegate work and start on worker thread.
    if (this->marqueeWorkerStarted == false) {
        this->marqueeWorker->start();
        this->marqueeWorkerStarted = true;
        this->marqueeWorker->renderCurrentState();
    }
    else
    {
        //render current position of the hello world.
        this->marqueeWorker->renderCurrentState();
    }
}

void MarqueeConsole::process()
{
    std::stringstream commandText;
    commandText << std::string("Enter a command for ") << this->name << ": " << this->currentCommand;
    String toDisplay = commandText.str();
    int cursorPosition = toDisplay.length();
    ConsoleManager::getInstance()->setCursorPosition(0, Console::HEIGHT - 1);
    std::cout << toDisplay;

    if (isKeyPressed()) {
        char ch = getPressedKey();
        if (ch == '\b' && this->currentCommand.length() > 0)
        {
            this->currentCommand.pop_back();
            this->commandEntered = false;
        }
    	else if (ch != '\n' && ch != '\r')
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

    ConsoleManager::getInstance()->setCursorPosition(0, Console::HEIGHT);
    std::cout << this->outputBuffer.str();

    //move cursor to last character
    ConsoleManager::getInstance()->setCursorPosition(cursorPosition, Console::HEIGHT - 1);
    IETThread::sleep(POLLING_DELAY);
}

