#include "BaseScreen.h"

#include "ConsoleManager.h"

BaseScreen::BaseScreen(std::shared_ptr<Process> process, String processName) : AConsole(processName)
{
	this->attachedProcess = process;
}

void BaseScreen::onEnabled()
{
}

void BaseScreen::process()
{
	if(this->refreshed == false)
	{
		this->refreshed = true;
		this->printProcessInfo();
	}

	std::cout << "root:\\>";

	// Read user input
	std::string command;
	std::getline(std::cin, command);

	if (command == "clear" || command == "cls") {
		system("cls");
	}
	else if(command == "process-smi")
	{
		this->printProcessInfo();
	}
	else if(command == "exit")
	{
		ConsoleManager::getInstance()->returnToPreviousConsole();
		ConsoleManager::getInstance()->unregisterScreen(this->name);
	}
	else
	{
		std::cout << "Unknown command: " << command << std::endl;
	}
}

void BaseScreen::display()
{

}

void BaseScreen::printProcessInfo() const
{
	std::cout << "Process: " << this->name << std::endl;
	std::cout << "ID: " << this->attachedProcess->getPID() << std::endl;

	std::cout << std::endl;

	Process::CommandInfo cInfo = this->attachedProcess->getCurrentCommandInfo();
	std::cout << "Current instruction line: " << cInfo.currentCounter << std::endl;
	std::cout << "Lines of code: " << cInfo.linesOfCode << std::endl;
}
