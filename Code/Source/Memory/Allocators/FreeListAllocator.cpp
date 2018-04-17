#include "FreeListAllocator.h"

#include "Alignment.h"
#include "Helpers/MemoryChunkHelpers.h"
#include "MemoryChunk.h"
#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Memory)

struct AllocationHeader
{
	uint8_t m_Adjustment;
	size_t m_Size;
};

FreeListAllocator::FreeListAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize)
	: AllocatorBase(a_BaseAddress, a_ByteSize)
{
	AssertMessage(sizeof(MemoryChunk) + sizeof(uint32_t) < a_ByteSize, "Allocated memory block size is too small for a free list allocator!");
	MemoryChunk *memoryChunk = reinterpret_cast<MemoryChunk*>(m_BaseAddress);
	memoryChunk->m_Size = a_ByteSize;
	memoryChunk->m_Next = nullptr;
	m_FreeList.InsertFront(memoryChunk);
}

FreeListAllocator::~FreeListAllocator()
{
	m_FreeList.Clear();
}

void* FreeListAllocator::Allocate(size_t a_Size, uint8_t a_Alignment)
{
	AssertMessage(0 != a_Size, "Invalid size to allocate!");
	AssertMessage(0 != a_Alignment, "Invalid alignment requested!");

	uint8_t padding = 0;
	FreeList::Iterator previousFreeChunk = m_FreeList.Begin();
	MemoryChunk *memoryChunk = FindFirstChunk(a_Size, a_Alignment, previousFreeChunk, padding);
	const size_t totalBlockSize = a_Size + padding;
	if (totalBlockSize < memoryChunk->m_Size)
	{
		SplitChunk(memoryChunk, totalBlockSize, previousFreeChunk);
		m_FreeList.Erase(previousFreeChunk);
	}

	uintptr_t dataAddress = reinterpret_cast<uintptr_t>(memoryChunk) + padding;
	uintptr_t headerAddress = dataAddress - sizeof(AllocationHeader);
	AllocationHeader *allocationHeader = reinterpret_cast<AllocationHeader*>(headerAddress);
	allocationHeader->m_Adjustment = padding; // <- incorrect; need to know padding up to allocationheader which is 0 in the first test case
	allocationHeader->m_Size = totalBlockSize;

// 	m_used += requiredSize;
// 	m_peak = std::max(m_peak, m_used);

	return reinterpret_cast<void*>(dataAddress);
}

void FreeListAllocator::Deallocate(void *a_Ptr)
{
	UNUSED(a_Ptr);
}

#if defined(_DEBUG)
void FreeListAllocator::CheckCoherence()
{
}
#endif

MemoryChunk* FreeListAllocator::FindFirstChunk(size_t a_RequestedSize, uint8_t a_Alignment, FreeList::Iterator &a_PreviousChunk, uint8_t &a_Adjustment)
{
	MemoryChunk *freeChunk = nullptr;
	FreeList::Iterator pos = m_FreeList.Begin();
	while (m_FreeList.End() != pos && nullptr == freeChunk)
	{
		MemoryChunk* chunk = reinterpret_cast<MemoryChunk*>(*pos);
		a_Adjustment = AlignmentAdjustment(reinterpret_cast<uintptr_t>(chunk), a_Alignment, sizeof(AllocationHeader));
		const size_t totalSize = a_RequestedSize + a_Adjustment;
		if (chunk->m_Size >= totalSize)
		{
			freeChunk = *pos;
			break;
		}
		a_PreviousChunk = pos;
		++pos;
	}

	AssertMessage(nullptr != freeChunk, "Unable to find memory chunk of sufficient size!");
	return freeChunk;
}

void FreeListAllocator::SplitChunk(MemoryChunk *a_MemoryChunk, size_t a_RequestedSize, FreeList::Iterator &a_PreviousChunk)
{
	AssertMessage(nullptr != a_MemoryChunk, "Attempt to split an invalid memory chunk!");
	MemoryChunk *memoryChunk = reinterpret_cast<MemoryChunk*>(reinterpret_cast<uintptr_t>(a_MemoryChunk) + a_RequestedSize);
	memoryChunk->m_Size = a_MemoryChunk->m_Size - a_RequestedSize;
	memoryChunk->m_Next = a_MemoryChunk->m_Next;
	a_MemoryChunk->m_Size = a_RequestedSize;
	m_FreeList.Insert(a_PreviousChunk + 1, memoryChunk);
}

END_NAMESPACE(Memory)
