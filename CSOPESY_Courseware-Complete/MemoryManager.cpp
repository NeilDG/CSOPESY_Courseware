#include "MemoryManager.h"
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
	}
	else
	{
		this->memoryAllocator = nullptr;
	}
}

void* MemoryManager::allocate(size_t size) const
{
	return this->memoryAllocator->allocate(size);
}

void MemoryManager::deallocate(void* ptr, size_t size) const
{
	this->memoryAllocator->deallocate(ptr, size);
}

String MemoryManager::visualizeMemory() const
{
	return this->memoryAllocator->visualizeMemory();
}
