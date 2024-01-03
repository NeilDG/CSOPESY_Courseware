#pragma once
struct Delay
{
	static constexpr int PER_INSTRUCTION_DELAY = 10; //set instruction delay to add some sleep per execution.
	static constexpr int PER_PROCESS_DELAY = 1; //set per process delay before moving into next process in CPU scheduler
	static constexpr int REFRESH_DELAY = 10; //screen refresh in marquee console
	static constexpr int POLLING_DELAY = 5; //keyboard polling rate. Lower is better.
};

struct Console
{
	static constexpr int WIDTH = 120; //screen refresh in marquee console
	static constexpr int HEIGHT = 25; //keyboard polling rate. Lower is better.
};

struct SchedulerType
{
	//0 = debug, 1 = FCFS, 2 = SJF (No-prempt), 3 = SJF (Preempt), 4 = Round-robin
	static constexpr int SCHEDULER_TYPE = 1;
};

struct ProcessRequirementFlags_CONFIG
{
	static constexpr bool REQUIRE_FILES = false;
	static constexpr int NUM_FILES = 0;
	static constexpr bool REQUIRE_MEMORY = false;
	static constexpr int MEMORY_REQUIRED = 0;
};

struct MemoryAllocatorType
{
	//0 = no memory allocation emulation, 1 = flat memory allocator, 2= segmentation, 3 = paging
	static constexpr int MEMORY_ALLOCATOR_TYPE = 1;
	static constexpr int MAXIMUM_MEMORY_SIZE = 64;
};
