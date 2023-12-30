#include "SchedulingConsole.h"
#include "ConsoleManager.h"
#include "DebugScheduler.h"
#include "IETThread.h"
#include "InputManager.h"
#include "MessageBuffer.h"

SchedulingConsole::SchedulingConsole() : AConsole(SCHEDULING_CONSOLE)
{
    this->debugScheduler = std::make_shared<DebugScheduler>();
    this->debugScheduler->test_storeRandomProcessesInQueue(50);

    // this->chosenConsole = std::make_unique<Scheduling_UIVersion1>(this->debugScheduler);
    this->chosenConsole = std::make_unique<Scheduling_UIVersion2>(this->debugScheduler);
}

void SchedulingConsole::onEnabled()
{

}

void SchedulingConsole::process()
{
    this->chosenConsole->process();
}


void SchedulingConsole::display()
{
    this->chosenConsole->display();
}

Scheduling_UIVersion1::Scheduling_UIVersion1(std::shared_ptr<DebugScheduler> scheduler) : AConsole(SCHEDULING_CONSOLE)
{
    this->scheduler = scheduler;
    this->messageRow = 3;
}

void Scheduling_UIVersion1::onEnabled()
{
}

void Scheduling_UIVersion1::process()
{
    std::stringstream commandText;
    commandText << std::string("Enter a command for ") << this->name << ": " << this->currentCommand;
    this->btmCommandDisplay = commandText.str();
    this->btmCommandPosition = this->btmCommandDisplay.length();

    if (InputManager::getInstance()->isKeyPressed()) {
        char ch = InputManager::getInstance()->getPressedKey();
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

    this->scheduler->execute();
    IETThread::sleep(Delay::POLLING_DELAY);
}

void Scheduling_UIVersion1::display()
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

Scheduling_UIVersion2::Scheduling_UIVersion2(std::shared_ptr<DebugScheduler> scheduler) : AConsole(SCHEDULING_CONSOLE)
{
    this->scheduler = scheduler;
    this->ui2flags.schedulerRunning = false;
    this->ui2flags.printHeader = true;
}

void Scheduling_UIVersion2::onEnabled()
{
}

void Scheduling_UIVersion2::process()
{
    //do nothing except for starting the scheduler thread. UI console is input-based per frame.
    if (this->ui2flags.schedulerRunning == false) {
        this->ui2flags.schedulerRunning = true;
        this->scheduler->start();
    }
}

void Scheduling_UIVersion2::display()
{
    if (this->ui2flags.printHeader)
    {
        ConsoleManager::getInstance()->setCursorPosition(0, 0);
        std::cout << "*****************************************" << std::endl;
        std::cout << "* Displaying a scheduling console! *" << std::endl;
        std::cout << "*****************************************" << std::endl;
        this->ui2flags.printHeader = false;
    }
    std::vector<DebugScheduler::ProcessTimeInfo> ptList = this->scheduler->getAllProcessRemainingTime();

    std::cout << "Enter command: ";
    String command;
    std::getline(std::cin, command);

    if (command == "csopesy-smi" || command == "nvidia-smi")
    {
        std::cout << "One bar means one command/remaining time." << std::endl;
        for (int i = 0; i < ptList.size(); i++)
        {
            DebugScheduler::ProcessTimeInfo ptInfo = ptList[i];
            std::cout << "PID:" << ptInfo.pid << " ";

            if (ptInfo.remainingTime > 0)
            {
                for (int j = 0; j < ptInfo.remainingTime; j++)
                {
                    std::cout << "=";
                }
            }
            else
            {
                std::cout << "Finished";
            }

            std::cout << std::endl;
        }
    }
    else if (command == "clear") {
        system("cls");  // Clear screen if 'clear' is entered
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
