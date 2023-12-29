#pragma once
#include "AConsole.h"
class MainConsole :    public AConsole
{
public:
	MainConsole();
	void display() override;
	void process() override;

private:
	void DisplayCSOPESY() const;
};

