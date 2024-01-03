#include "FlatMemoryAllocator.h"
#include <iostream>
#include <sstream>

FlatMemoryAllocator::FlatMemoryAllocator(size_t maximumSize)
{
	this->maximumSize = maximumSize;
	this->currentAllocatedSize = 0;
	this->memoryBlock.resize(this->maximumSize, 0);
	this->freeBlocks.push_back(MemoryBlock{0, this->maximumSize});
}

void* FlatMemoryAllocator::allocate(size_t size)
{
	const MemoryBlockFindResult findBlockResult = this->findFreeBlock(size);

	if(findBlockResult.blockFound)
	{
		// Mark the block as allocated
		MemoryBlock& allocatedBlock = this->freeBlocks[findBlockResult.freeBlockIndex];
		allocatedBlock.size = size;

		this->currentAllocatedSize += size;

		return &memoryBlock[allocatedBlock.start];
	}
	else
	{
		std::cerr << "Memory allocation failed. Insufficient memory." << std::endl;
		return nullptr;
	}
}

void FlatMemoryAllocator::deallocate(void* ptr, size_t size)
{
	// Find the MemoryBlock corresponding to the deallocated pointer
	for (size_t i = 0; i < freeBlocks.size(); ++i) {
		if (&memoryBlock[freeBlocks[i].start] == ptr) {
			// Mark the block as free
			//freeBlocks[i].size = 0;

			// Update the total allocated size
			this->currentAllocatedSize -= freeBlocks[i].size;

			return;  // Found and deallocated, exit the function
		}
	}

	// If the loop completes without finding the block, print an error message
	std::cerr << "Invalid deallocation. The pointer does not belong to this memory manager." << std::endl;
}

String FlatMemoryAllocator::visualizeMemory()
{
	std::stringstream outputBuffer;
	outputBuffer << String("Memory Visualization:") << std::endl;
	outputBuffer << String("+");
	for (size_t i = 0; i < this->maximumSize; ++i) {
		outputBuffer << String("-");
	}
	outputBuffer << String("+") << std::endl;

	outputBuffer << String("Num free blocks: ") << freeBlocks.size() << std::endl;
	for (const auto& block : freeBlocks) {
		outputBuffer << String("|");
		for (size_t i = 0; i < block.start; ++i) {
			outputBuffer << String(" ");
		}
		for (size_t i = 0; i < block.size; ++i) {
			outputBuffer << String(".");
		}
	}
	outputBuffer << String("|");

	int difference = this->maximumSize - this->currentAllocatedSize;
	for (size_t i = 0; i < difference && difference > 0; ++i) {
		outputBuffer << String(" ");
	}
	for (size_t i = 0; i < this->currentAllocatedSize; ++i) {
		outputBuffer << String("#");
	}

	outputBuffer << String("|") << std::endl;

	outputBuffer << String("+");
	for (size_t i = 0; i < this->maximumSize; ++i) {
		outputBuffer << String("-");
	}
	outputBuffer << String("+") << std::endl;

	return outputBuffer.str();
}
