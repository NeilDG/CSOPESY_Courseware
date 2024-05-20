#pragma once
/**
 * \brief Class for doing memory tests
 */
class MemoryTestRun
{
public:
	MemoryTestRun() = default;
	~MemoryTestRun() = default;
	static void run();

private:
	static void testAllocation_uint8();
	static void testAllocation_int32();
	static void testReAllocation_int32();

};

