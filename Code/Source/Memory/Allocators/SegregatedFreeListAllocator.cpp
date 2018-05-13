#include "SegregatedFreeListAllocator.h"

// #include "Alignment.h"
// #include "Helpers/MemoryChunkHelpers.h"
// #include "MemoryChunk.h"
#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Memory)

BEGIN_UNNAMEDNAMESPACE()

struct AllocationHeader
{
	uint8_t m_Adjustment;
	size_t m_Size;
};

END_UNNAMEDNAMESPACE()

SegregatedFreeListAllocator::SegregatedFreeListAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize)
	: AllocatorBase(a_BaseAddress, a_ByteSize)
{
}

SegregatedFreeListAllocator::~SegregatedFreeListAllocator()
{
}

void* SegregatedFreeListAllocator::Allocate(size_t a_Size, uint8_t a_Alignment)
{
	AssertMessage(0 != a_Size, "Invalid size to allocate!");
	AssertMessage(0 != a_Alignment, "Invalid alignment requested!");

	return nullptr;
}

void SegregatedFreeListAllocator::Deallocate(void *a_Ptr)
{
	ValidatePointer(a_Ptr);
}

END_NAMESPACE(Memory)
