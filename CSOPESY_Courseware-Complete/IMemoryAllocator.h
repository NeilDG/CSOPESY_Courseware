#pragma once
#include <vector>

#include "TypedefRepo.h"

/**
 * \brief Interface for the memory allocator. Uses size_t for the memory sizes to accept any types of object that needs memory.
 */
class IMemoryAllocator
{
public:
	enum MemoryAllocatorType
	{
		FLAT_MEMORY_ALLOCATOR,
		SEGMENTATION,
		PAGING,
	};
	virtual void* allocate(size_t size) = 0;
	virtual void deallocate(void* ptr, size_t size) = 0;
	virtual String visualizeMemory() = 0;

protected:
	MemoryAllocatorType memoryAllocatorType;
    struct MemoryBlock {
        size_t start;
        size_t size;

        bool operator<(const MemoryBlock& other) const {
            return start < other.start;
        }
    };

    size_t maximumSize;
    size_t currentAllocatedSize;

    std::vector<char> memoryBlock;
    std::vector<MemoryBlock> freeBlocks;

    struct MemoryBlockFindResult
    {
        size_t freeBlockIndex;
        bool blockFound;
    };

    MemoryBlockFindResult findFreeBlock(size_t size) const;
};

/**
 * \brief Finds a contiguous memory block given a size. Returns
 * \param size The intended memory size to look for
 * \return 
 */
inline IMemoryAllocator::MemoryBlockFindResult IMemoryAllocator::findFreeBlock(size_t size) const
{
    MemoryBlockFindResult findResult;

    for (size_t i = 0; i < freeBlocks.size(); i++) {
        if (freeBlocks[i].size >= size) {
            findResult.freeBlockIndex = i;
            findResult.blockFound = true;
            return findResult;
        }
    }

    // If the loop completes without finding a block, set index to -1 to indicate not found
    findResult.freeBlockIndex = -1;
    findResult.blockFound = false;
    return findResult;
}
