#include "AConsole.h"
#include <conio.h>

AConsole::AConsole(String name)
{
	this->name = name;
}

AConsole::String AConsole::getName()
{
	return this->name;
}
