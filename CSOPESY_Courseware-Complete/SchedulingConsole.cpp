#include "SchedulingConsole.h"
#include "ConsoleManager.h"
#include "DebugScheduler.h"
#include "IETThread.h"

SchedulingConsole::SchedulingConsole() : AConsole(SCHEDULING_CONSOLE)
{

}

void SchedulingConsole::display()
{
    system("cls"); // Clear screen
    std::cout << "*****************************************" << std::endl;
    std::cout << "* Displaying a scheduling console! *" << std::endl;
    std::cout << "*****************************************" << std::endl;

	DebugScheduler debugScheduler;
	debugScheduler.test_storeRandomProcessesInQueue(50);
	debugScheduler.execute();
}

bool SchedulingConsole::processCommand()
{
    // std::stringstream commandText;
    // commandText << std::string("Enter a command for ") << this->name << ": " << this->currentCommand;
    //
    // String toDisplay = commandText.str();
    // int cursorPosition = toDisplay.length();
    // ConsoleManager::getInstance()->setCursorPosition(0, this->screenHeight - 1);
    // std::cout << toDisplay;
    //
    // if (isKeyPressed()) {
    //     char ch = getPressedKey();
    //     if (ch == '\b' && this->currentCommand.length() > 0)
    //     {
    //         this->currentCommand.pop_back();
    //         this->commandEntered = false;
    //     }
    //     else if (ch != '\n' && ch != '\r')
    //     {
    //         this->currentCommand.push_back(ch);
    //         this->commandEntered = false;
    //     }
    //     else
    //     {
    //         this->commandEntered = true;
    //     }
    // }
    //
    // if (this->commandEntered)
    // {
    //     //process commands
    //     if (this->currentCommand == "exit") {
    //         ConsoleManager::getInstance()->returnToPreviousConsole();
    //     }
    //     else if (this->currentCommand == "clear") {
    //         this->outputBuffer.str("");
    //         system("cls");  // Clear screen if 'clear' is entered
    //     }
    //     else {
    //         this->outputBuffer << std::string("Command processed in ") << this->name << ": " << this->currentCommand << std::endl;
    //     }
    //
    //     //reset flags
    //     this->commandEntered = false;
    //     this->currentCommand = "";
    // }
    //
    // ConsoleManager::getInstance()->setCursorPosition(0, this->screenHeight);
    // std::cout << this->outputBuffer.str();
    //
    // //move cursor to last character
    // ConsoleManager::getInstance()->setCursorPosition(cursorPosition, this->screenHeight - 1);
    // IETThread::sleep(10);

    return false;
}
