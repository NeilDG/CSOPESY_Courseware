#include "SchedulingConsole.h"
#include "ConsoleManager.h"
#include "DebugScheduler.h"
#include "IETThread.h"

SchedulingConsole::SchedulingConsole() : AConsole(SCHEDULING_CONSOLE)
{
    this->debugScheduler = std::make_unique<DebugScheduler>();
    this->debugScheduler->test_storeRandomProcessesInQueue(50);

    this->messageRow = 3;
}

void SchedulingConsole::display()
{
    // system("cls"); // Clear screen
    ConsoleManager::getInstance()->setCursorPosition(0, 0);
    std::cout << "*****************************************" << std::endl;
    std::cout << "* Displaying a scheduling console! *" << std::endl;
    std::cout << "*****************************************" << std::endl;

    //clear the current row
    ConsoleManager::getInstance()->setCursorPosition(0, this->messageRow);
    std::string spaces(Console::WIDTH, ' ');
    std::cout << spaces;
    ConsoleManager::getInstance()->setCursorPosition(0, this->messageRow);

    this->debugScheduler->execute();
    this->messageRow = (this->messageRow + 1) % (Console::HEIGHT - 2);
}

bool SchedulingConsole::processCommand()
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
    
    if (this->commandEntered)
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
        this->currentCommand = "";
        this->commandEntered = false;
    }
    
    ConsoleManager::getInstance()->setCursorPosition(0, Console::HEIGHT);
    std::cout << this->outputBuffer.str();
    
    //move cursor to last character
    ConsoleManager::getInstance()->setCursorPosition(cursorPosition, Console::HEIGHT - 1);
    IETThread::sleep(Delay::POLLING_DELAY);

    return false;
}
