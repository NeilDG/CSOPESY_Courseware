#pragma once
#include "AConsole.h"
class MainConsole :    public AConsole
{
public:
	MainConsole();
	void display() override;
	bool processCommand() override;

private:
	void DisplayCSOPESY() const;
};

