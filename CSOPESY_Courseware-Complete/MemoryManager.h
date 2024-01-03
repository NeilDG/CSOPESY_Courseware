#pragma once
#include <memory>

#include "IMemoryAllocator.h"

class MemoryManager
{
public:
	static MemoryManager* getInstance();
	static void initialize();
	static void destroy();

	void* allocate(size_t size) const;
	void deallocate(void* ptr, size_t size) const;
	String visualizeMemory() const;

private:
	MemoryManager();
	~MemoryManager() = default;
	MemoryManager(MemoryManager const&) {}; // copy constructor is private
	MemoryManager& operator=(MemoryManager const&) {}; // assignment operator is private*/
	static MemoryManager* sharedInstance;

	std::shared_ptr<IMemoryAllocator> memoryAllocator;

};

