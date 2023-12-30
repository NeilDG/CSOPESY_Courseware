#include "SchedulingConsole.h"
#include "ConsoleManager.h"
#include "DebugScheduler.h"
#include "IETThread.h"
#include "MessageBuffer.h"

SchedulingConsole::SchedulingConsole() : AConsole(SCHEDULING_CONSOLE)
{
    this->debugScheduler = std::make_unique<DebugScheduler>();
    this->debugScheduler->test_storeRandomProcessesInQueue(50);

    this->messageRow = 3;
}

void SchedulingConsole::onEnabled()
{

}

void SchedulingConsole::process()
{
    std::stringstream commandText;
    commandText << std::string("Enter a command for ") << this->name << ": " << this->currentCommand;
    this->btmCommandDisplay = commandText.str();
    this->btmCommandPosition = this->btmCommandDisplay.length();

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

    // this->debugScheduler->execute();
    IETThread::sleep(Delay::POLLING_DELAY);
}

void SchedulingConsole::displayUI_Version1()
{
    ConsoleManager::getInstance()->setCursorPosition(0, 0);
    std::cout << "*****************************************" << std::endl;
    std::cout << "* Displaying a scheduling console! *" << std::endl;
    std::cout << "*****************************************" << std::endl;

    if (MessageBuffer::hasBacklogMessages())
    {
        //clear the current row
        ConsoleManager::getInstance()->setCursorPosition(0, this->messageRow);
        std::string spaces(Console::WIDTH, ' ');
        std::cout << spaces;
        ConsoleManager::getInstance()->setCursorPosition(0, this->messageRow);

        // this->debugScheduler->execute();
        MessageBuffer::printBacklogMessages();
        this->messageRow = (this->messageRow + 1) % (Console::HEIGHT - 2);
    }

    //typing command row
    ConsoleManager::getInstance()->setCursorPosition(0, Console::HEIGHT - 1);
    std::cout << this->btmCommandDisplay;

    ConsoleManager::getInstance()->setCursorPosition(0, Console::HEIGHT);
    std::cout << this->outputBuffer.str();

    ConsoleManager::getInstance()->setCursorPosition(this->btmCommandPosition, Console::HEIGHT - 1);
}

void SchedulingConsole::displayUI_Version2()
{
    ConsoleManager::getInstance()->setCursorPosition(0, 0);
    std::cout << "*****************************************" << std::endl;
    std::cout << "* Displaying a scheduling console! *" << std::endl;
    std::cout << "*****************************************" << std::endl;
    std::vector<DebugScheduler::ProcessTimeInfo> ptList = this->debugScheduler->getAllProcessRemainingTime();


	for(int i = 0; i < ptList.size(); i++)
    {
		DebugScheduler::ProcessTimeInfo ptInfo = ptList[i];
        std::cout << "PID:" << ptInfo.pid << " ========" <<std::endl;
    }

    // //typing command row
    // int yLoc = Console::HEIGHT + ptList.size();
    // ConsoleManager::getInstance()->setCursorPosition(0, yLoc - 1);
    // std::cout << this->btmCommandDisplay;
    //
    // ConsoleManager::getInstance()->setCursorPosition(0, yLoc);
    // std::cout << this->outputBuffer.str();
    //
    // ConsoleManager::getInstance()->setCursorPosition(this->btmCommandPosition, yLoc - 1);
}

void SchedulingConsole::display()
{
    // this->displayUI_Version1();
    this->displayUI_Version2();
}
