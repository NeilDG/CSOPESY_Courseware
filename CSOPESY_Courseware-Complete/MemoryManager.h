#pragma once
#include <memory>

#include "IMemoryAllocator.h"


const String NO_MEMORY_ALLOCATOR_STRING = "NoMemory-Emulation";
const String FLAT_MEMORY_ALLOCATOR_STRING = "FlatMemory";
const String SEGMENTATION_ALLOCATOR_STRING = "Segmentation";
const String PAGING_ALLOCATOR_STRING = "Paging";

class MemoryManager
{
public:
	static MemoryManager* getInstance();
	static void initialize();
	static void destroy();

	void* allocate(size_t size) const;
	void deallocate(void* ptr) const;
	String visualizeMemory() const;
	String getMemoryAllocatorName();

	//test functions
	static void test_MemoryAllocation();

private:
	MemoryManager();
	~MemoryManager() = default;
	MemoryManager(MemoryManager const&) {}; // copy constructor is private
	MemoryManager& operator=(MemoryManager const&) {}; // assignment operator is private*/
	static MemoryManager* sharedInstance;

	std::shared_ptr<IMemoryAllocator> memoryAllocator;
	String memoryAllocatorName;

};

