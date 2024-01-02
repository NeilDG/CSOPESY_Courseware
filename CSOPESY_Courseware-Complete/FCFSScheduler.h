#pragma once
#include "AScheduler.h"

class FCFSScheduler :    public AScheduler
{
public:
	FCFSScheduler();
	void execute() override;
};

