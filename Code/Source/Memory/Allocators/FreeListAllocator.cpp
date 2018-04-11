#include "FreeListAllocator.h"

#include "Alignment.h"
#include "Helpers/MemoryChunkHelpers.h"
#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Memory)

struct MemoryChunk
{
	MemoryChunk *m_Next = nullptr;
	size_t m_Size;
};

struct AllocationHeader
{
	uint8_t m_Adjustment;
	size_t m_Size;
};

FreeListAllocator::FreeListAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize)
	: AllocatorBase(a_BaseAddress, a_ByteSize)
{
	AssertMessage(sizeof(MemoryChunk) + sizeof(uint32_t) < a_ByteSize, "Allocated memory block size is too small for a free list allocator!");
	m_FreeList = reinterpret_cast<MemoryChunk*>(m_BaseAddress);
	m_FreeList->m_Size = a_ByteSize;
	m_FreeList->m_Next = nullptr;
}

FreeListAllocator::~FreeListAllocator()
{
	m_FreeList = nullptr;
}

void* FreeListAllocator::Allocate(size_t a_Size, uint8_t a_Alignment)
{
	AssertMessage(0 != a_Size, "Invalid size to allocate!");
	AssertMessage(0 != a_Alignment, "Invalid alignment requested!");

	MemoryChunk *freeChunk = m_FreeList;
	MemoryChunk *previousFreeChunk = nullptr;
	while (nullptr != freeChunk)
	{
		const uint8_t adjustment = AlignmentAdjustment(reinterpret_cast<uintptr_t>(freeChunk), a_Alignment, sizeof(AllocationHeader));
		size_t totalSize = adjustment + a_Size;
		if (freeChunk->m_Size < totalSize)
		{
			previousFreeChunk = freeChunk;
			freeChunk = freeChunk->m_Next;
			continue;
		}

		if (freeChunk->m_Size - totalSize <= sizeof(AllocationHeader))
		{
			AssertMessage("Check when this happens!");
			//Increase allocation size instead of creating a new FreeBlock 
			totalSize = freeChunk->m_Size;
			if (previousFreeChunk != nullptr)
			{
				previousFreeChunk->m_Next = freeChunk->m_Next;
			}
			else
			{
				m_FreeList = freeChunk->m_Next;
			}
		}
		else
		{
			MemoryChunk* nextChunk = reinterpret_cast<MemoryChunk*>(reinterpret_cast<uintptr_t>(freeChunk) + totalSize);
			nextChunk->m_Size = freeChunk->m_Size - totalSize;
			nextChunk->m_Next = freeChunk->m_Next;
			if (previousFreeChunk != nullptr)
			{
				previousFreeChunk->m_Next = nextChunk;
			}
			else
			{
				m_FreeList = nextChunk;
			}
		}

		uintptr_t alignedAddress = (uintptr_t)freeChunk + adjustment;
		AllocationHeader* header = (AllocationHeader*)(alignedAddress - sizeof(AllocationHeader));
		header->m_Size = totalSize;
		header->m_Adjustment = adjustment;

		m_MemoryAllocated += totalSize;
		m_NumAllocations++;
		
		AssertMessage(IsAligned(reinterpret_cast<void*>(alignedAddress), a_Alignment), "Allocated memory address is not properly aligned!");
		return reinterpret_cast<void*>(alignedAddress);
	}

	return nullptr;
}

void FreeListAllocator::Deallocate(void *a_Ptr)
{
	const uintptr_t ptr = reinterpret_cast<uintptr_t>(a_Ptr);
	AllocationHeader* header = reinterpret_cast<AllocationHeader*>(ptr - sizeof(AllocationHeader));	
	const uintptr_t allocationStartAddress = ptr - header->m_Adjustment;
	const uintptr_t allocationEndAddress = allocationStartAddress + header->m_Size;

	MemoryChunk *freeChunk = m_FreeList;
	MemoryChunk *previousFreeChunk = nullptr;
	while (nullptr != freeChunk)
	{
		uintptr_t freeChunkAddress = reinterpret_cast<uintptr_t>(freeChunk);
		if (freeChunkAddress > allocationEndAddress)
		{
			break;
		}
		previousFreeChunk = freeChunk;
		freeChunk = freeChunk->m_Next;
	}

	if (nullptr == previousFreeChunk)
	{
		// add as new head in the free list
		previousFreeChunk = reinterpret_cast<MemoryChunk*>(allocationStartAddress);
		previousFreeChunk->m_Size = header->m_Size;
		previousFreeChunk->m_Next = m_FreeList;
		m_FreeList = previousFreeChunk;
	}
	else if ((reinterpret_cast<uintptr_t>(previousFreeChunk) + previousFreeChunk->m_Size) == allocationStartAddress)
	{
		// merge with previous block
		previousFreeChunk->m_Size += header->m_Size;
	}
	else
	{
		AssertMessage("Odd functionality; check!");
		// add at the end of the free list
		MemoryChunk *tail = reinterpret_cast<MemoryChunk*>(allocationStartAddress);
		tail->m_Size = header->m_Size;
		tail->m_Next = previousFreeChunk->m_Next;
		previousFreeChunk->m_Next = tail;
		previousFreeChunk = tail;			// ???
	}

	if (nullptr != freeChunk && reinterpret_cast<uintptr_t>(freeChunk) == allocationEndAddress)
	{
		AssertMessage("Check when this happens!");
		// merge with previous block at the end of the list?
		previousFreeChunk->m_Size += freeChunk->m_Size;
		previousFreeChunk->m_Next = freeChunk->m_Next;
	}

	m_NumAllocations--;
	m_MemoryAllocated -= header->m_Size;
}

#if defined(_DEBUG)
void FreeListAllocator::CheckCoherence()
{
}
#endif

void* FreeListAllocator::FindFirstChunk(size_t a_RequestedSize, uint8_t a_Alignment)
{
	UNUSED(a_Alignment);
	UNUSED(a_RequestedSize);
	return nullptr;
}

END_NAMESPACE(Memory)
