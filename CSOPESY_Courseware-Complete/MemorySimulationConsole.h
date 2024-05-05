#pragma once
#include "AConsole.h"
#include "AScheduler.h"
#include "IMemoryAllocator.h"

class MemorySimulationConsole :    public AConsole
{
public:
	MemorySimulationConsole();
	void onEnabled() override;
	void display() override;
	void process() override;

private:
	void printHeaderBorder() const;
	void test_mockupUI();

	std::shared_ptr<AScheduler> scheduler;
	std::shared_ptr<IMemoryAllocator> memoryAllocator;
	bool printHeader = true;

};

