#pragma once
#include "IMemoryAllocator.h"
class FlatMemoryAllocator :    public IMemoryAllocator
{
public:
	FlatMemoryAllocator(size_t maximumSize);
	void* allocate(size_t size) override;
	void deallocate(void* ptr) override;
	String visualizeMemory() override;
};

