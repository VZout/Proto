#include "FreeListAllocator.h"

#include "Alignment.h"
#include "Helpers/MemoryChunkHelpers.h"
#include "MemoryChunk.h"
#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Memory)

BEGIN_UNNAMEDNAMESPACE()

size_t CalculateTotalBlockSize(size_t a_Size, uint8_t a_Padding)
{
#if !defined(NDEBUG)
	return a_Size + a_Padding + sizeof(g_FooterGuardValue);
#else
	return a_Size + a_Padding;
#endif
}

#if !defined(NDEBUG)

void SetMemoryChunkGuards(MemoryChunk *a_MemoryChunk, size_t a_BlockSize)
{
	AssertMessage(NULLPTR != a_MemoryChunk, "Invalid memory chunk encountered!");
	*(reinterpret_cast<uint32_t*>(a_MemoryChunk)) = g_HeaderGuardValue;
	const uintptr_t footerGuard = reinterpret_cast<uintptr_t>(a_MemoryChunk) + a_BlockSize - sizeof(g_FooterGuardValue);
	*(reinterpret_cast<uint32_t*>(footerGuard)) = g_FooterGuardValue;
}

void ValidateMemoryChunkGuards(const MemoryChunk* const a_MemoryChunk, size_t a_BlockSize)
{
	AssertMessage(NULLPTR != a_MemoryChunk , "Invalid memory chunk encountered!");
	AssertMessage(g_HeaderGuardValue == *(reinterpret_cast<const uint32_t*>(a_MemoryChunk)), "Invalid memory chunk header guard encountered!");
	const uintptr_t footerGuard = reinterpret_cast<uintptr_t>(a_MemoryChunk) + a_BlockSize - sizeof(g_FooterGuardValue);
	AssertMessage(g_FooterGuardValue == *(reinterpret_cast<uint32_t*>(footerGuard)), "Invalid memory chunk footer guard encountered!");
}

#endif

END_UNNAMEDNAMESPACE()

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
	memoryChunk->m_Next = NULLPTR;
	m_FreeList.Insert(memoryChunk);
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
	MemoryChunk *memoryChunk = FindFirstChunk(a_Size, a_Alignment, padding);
	const size_t totalBlockSize = CalculateTotalBlockSize(a_Size, padding);
	if (totalBlockSize < memoryChunk->m_Size)
	{
		SplitChunk(memoryChunk, totalBlockSize);
		AssertMessage(totalBlockSize == memoryChunk->m_Size, "Error splitting memory chunk!");
		m_FreeList.Erase(memoryChunk);
	}
	SetMemoryChunkGuards(memoryChunk, totalBlockSize);

	const uintptr_t dataAddress = reinterpret_cast<uintptr_t>(memoryChunk) + padding;
	const uintptr_t headerAddress = dataAddress - sizeof(AllocationHeader);
	AllocationHeader *allocationHeader = reinterpret_cast<AllocationHeader*>(headerAddress);
	allocationHeader->m_Adjustment = padding - sizeof(AllocationHeader);
	allocationHeader->m_Size = totalBlockSize;
	UpdateAllocations(totalBlockSize);
	return reinterpret_cast<void*>(dataAddress);
}

void FreeListAllocator::Deallocate(void *a_Ptr)
{
	const uintptr_t dataAddress = reinterpret_cast<uintptr_t>(a_Ptr);
	AssertMessage(dataAddress >= m_BaseAddress && dataAddress <= (m_BaseAddress + m_ByteSize), "Pointer has not been allocated by this allocator!");
	AllocationHeader *allocationHeader = reinterpret_cast<AllocationHeader*>(dataAddress - sizeof(AllocationHeader));

	const size_t blockSize = allocationHeader->m_Size;
	MemoryChunk *memoryChunk = reinterpret_cast<MemoryChunk*>(dataAddress - sizeof(AllocationHeader) - allocationHeader->m_Adjustment);
	ValidateMemoryChunkGuards(memoryChunk, blockSize);

	m_FreeList.Insert(memoryChunk);
	UpdateDeallocations(blockSize);
}

#if !defined(NDEBUG)
void FreeListAllocator::CheckCoherence()
{
}
#endif

MemoryChunk* FreeListAllocator::FindFirstChunk(size_t a_RequestedSize, uint8_t a_Alignment, uint8_t &a_Adjustment)
{
	MemoryChunk *freeChunk = NULLPTR;
	FreeList::Iterator pos = m_FreeList.Begin();
	while (m_FreeList.End() != pos && NULLPTR == freeChunk)
	{
		MemoryChunk* chunk = reinterpret_cast<MemoryChunk*>(*pos);
#if !defined(NDEBUG)
		a_Adjustment = AlignmentAdjustment(reinterpret_cast<uintptr_t>(chunk), a_Alignment, sizeof(AllocationHeader) + sizeof(g_HeaderGuardValue));
		const size_t totalSize = a_RequestedSize + a_Adjustment + sizeof(g_FooterGuardValue);
#else
		a_Adjustment = AlignmentAdjustment(reinterpret_cast<uintptr_t>(chunk), a_Alignment, sizeof(AllocationHeader));
		const size_t totalSize = a_RequestedSize + a_Adjustment;
#endif
		if (chunk->m_Size >= totalSize)
		{
			freeChunk = *pos;
			break;
		}
		++pos;
	}

	AssertMessage(NULLPTR != freeChunk, "Unable to find memory chunk of sufficient size!");
	return freeChunk;
}

void FreeListAllocator::SplitChunk(MemoryChunk *a_MemoryChunk, size_t a_RequestedSize)
{
	AssertMessage(NULLPTR != a_MemoryChunk, "Attempt to split an invalid memory chunk!");
	MemoryChunk *memoryChunk = reinterpret_cast<MemoryChunk*>(reinterpret_cast<uintptr_t>(a_MemoryChunk) + a_RequestedSize);
	memoryChunk->m_Size = a_MemoryChunk->m_Size - a_RequestedSize;
	memoryChunk->m_Next = a_MemoryChunk->m_Next;
	a_MemoryChunk->m_Size = a_RequestedSize;
	m_FreeList.Insert(memoryChunk);
}

END_NAMESPACE(Memory)
