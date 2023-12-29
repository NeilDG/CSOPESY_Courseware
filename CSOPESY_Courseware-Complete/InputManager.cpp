#include "InputManager.h"

#include <conio.h>

InputManager* InputManager::sharedInstance = nullptr;
InputManager* InputManager::getInstance()
{
	return sharedInstance;
}

void InputManager::initialize()
{
	sharedInstance = new InputManager();
}

void InputManager::destroy()
{
	delete sharedInstance;
}

bool InputManager::isKeyPressed()
{
	return _kbhit() != 0;
}

char InputManager::getPressedKey()
{
	return _getch();
}

InputManager::InputManager()
{
}
