#pragma once
#include "AConsole.h"
class MainConsole :    public AConsole
{
public:
	MainConsole();
	void onEnabled() override;
	void display() override;
	void process() override;

private:
	void DisplayCSOPESY();
	bool refreshed = false;
};

