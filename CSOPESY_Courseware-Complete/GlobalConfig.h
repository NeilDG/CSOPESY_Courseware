#pragma once
#include "TypedefRepo.h"

struct Delay
{
	static constexpr int PER_INSTRUCTION_DELAY = 10; //set instruction delay to add some sleep per execution.
	static constexpr int PER_PROCESS_DELAY = 0; //set per process delay before moving into next process in CPU scheduler
	static constexpr int REFRESH_DELAY = 10; //screen refresh in marquee console
	static constexpr int POLLING_DELAY = 5; //keyboard polling rate. Lower is better.
};
