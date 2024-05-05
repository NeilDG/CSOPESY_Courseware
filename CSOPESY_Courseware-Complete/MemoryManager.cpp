#include "MemoryManager.h"

#include <iostream>

#include "GlobalConfig.h"
#include "FlatMemoryAllocator.h"

MemoryManager* MemoryManager::sharedInstance = nullptr;
MemoryManager* MemoryManager::getInstance()
{
	return sharedInstance;
}

void MemoryManager::initialize()
{
	sharedInstance = new MemoryManager();
}

void MemoryManager::destroy()
{
	delete sharedInstance;
}

MemoryManager::MemoryManager()
{
	if(MemoryAllocatorType::MEMORY_ALLOCATOR_TYPE == 1)
	{
		this->memoryAllocator = std::make_shared<FlatMemoryAllocator>(MemoryAllocatorType::MAXIMUM_MEMORY_SIZE);
		this->memoryAllocatorName = FLAT_MEMORY_ALLOCATOR_STRING;
	}
	else
	{
		this->memoryAllocator = nullptr;
		this->memoryAllocatorName = NO_MEMORY_ALLOCATOR_STRING;
	}
}

void* MemoryManager::allocate(size_t size) const
{
	return this->memoryAllocator->allocate(size);
}

void MemoryManager::deallocate(void* ptr) const
{
	this->memoryAllocator->deallocate(ptr);
}

String MemoryManager::visualizeMemory() const
{
	return this->memoryAllocator->visualizeMemory();
}

String MemoryManager::getMemoryAllocatorName()
{
	return this->memoryAllocatorName;
}

void MemoryManager::test_MemoryAllocation()
{
	// Allocate memory
	MemoryManager* memoryManager = MemoryManager::getInstance();

	void* ptr1 = memoryManager->allocate(64);
	void* ptr2 = memoryManager->allocate(128);

	// Visualize memory
	std::cout << memoryManager->visualizeMemory();
	//
	// Deallocate memory
	memoryManager->deallocate(ptr1);
	memoryManager->deallocate(ptr2);

	// Visualize memory after deallocation
	std::cout << memoryManager->visualizeMemory();
}
