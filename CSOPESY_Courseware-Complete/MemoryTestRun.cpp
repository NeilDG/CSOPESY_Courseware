#include "MemoryTestRun.h"
#include <iostream>

void MemoryTestRun::run()
{
	testAllocation_uint8();
	testAllocation_int32();
    testReAllocation_int32();
}

void MemoryTestRun::testAllocation_uint8()
{
    std::cout << "--TEST ALLOCATION. UINT8--" << std::endl;
    const int MAX_SIZE = 10;

    // Allocate a block of memory to store MAX_SIZE * sizeof(uint8_t) bytes
    uint8_t* data = new uint8_t[MAX_SIZE * sizeof(uint8_t)];

    // Pointer to keep track of the next available position (offset in bytes)
    uint8_t* top = data;

    // Push 10 values (treated as uint8_t) onto the stack using placement new
    for (int i = 0; i < 10; ++i) {
        new (top) uint8_t(200); // Placement new to construct uint8_t at top
        top++;
    }

    // Access and print the elements (stack order - LIFO)
    while (top != data) {
        top--;
        std::cout << "Value: " << static_cast<int>(*top) << ", Address: " << reinterpret_cast<void*>(top) << std::endl;
    }

    std::cout << std::endl;

    // Deallocate the memory block (no placement delete needed)
    delete[] data;
}

void MemoryTestRun::testAllocation_int32()
{
    std::cout << "--TEST ALLOCATION. UINT32--" << std::endl;

    //ALLOCATION FOR SIGNED INT
    const int MAX_SIZE = 10;

	// Allocate a block of memory to store MAX_SIZE * sizeof(uint8_t) bytes
    int32_t* data = new int32_t[MAX_SIZE * sizeof(int32_t)];

    // Pointer to keep track of the next available position (offset in bytes)
    int32_t* top = data;

    // Push values onto the stack using placement new
    for (int i = 0; i < 10; ++i) {
        new (top) int32_t(15235521); // Placement new to construct uint8_t at top
        top++;
    }

    // Access and print the elements (stack order - LIFO)
    while (top != data) {
        top--;
        std::cout << "Value: " << static_cast<int>(*top) << ", Address: " << reinterpret_cast<void*>(top) << std::endl;
    }

    std::cout << std::endl;

    // Deallocate the memory block (no placement delete needed)
    delete[] data;

}

void MemoryTestRun::testReAllocation_int32()
{
    std::cout << "--TEST ALLOCATION WITH OVERWRITING. INT32--" << std::endl;

    //ALLOCATION FOR SIGNED INT
    const int MAX_SIZE = 10;

    // Allocate a block of memory to store MAX_SIZE * sizeof(uint8_t) bytes
    int32_t* data = new int32_t[MAX_SIZE * sizeof(int32_t)];

    // Pointer to keep track of the next available position (offset in bytes)
    int32_t* top = data;

    // Push values onto the stack using placement new
    for (int i = 0; i < 10; ++i) {
        new (top) int32_t(15235521); // Placement new to construct uint8_t at top
        top++;
    }

    // Access and print the elements (stack order - LIFO)
    while (top != data) {
        top--;
        std::cout << "Value: " << static_cast<int>(*top) << ", Address: " << reinterpret_cast<void*>(top) << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Re-allocating/overwriting data!" << std::endl;

    //reallocate new data
    //Push values onto the stack using placement new
    for (int i = 0; i < 10; ++i) {
        new (top) int32_t(-100); // Placement new to construct uint8_t at top
        top++;
    }

    // Access and print the elements (stack order - LIFO)
    while (top != data) {
        top--;
        std::cout << "Value: " << static_cast<int>(*top) << ", Address: " << reinterpret_cast<void*>(top) << std::endl;
    }
   

    std::cout << std::endl;

    // Deallocate the memory block (no placement delete needed)
    delete[] data;
}
