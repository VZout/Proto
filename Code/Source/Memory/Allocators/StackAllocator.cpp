#include "StackAllocator.h"

#include "Helpers/Alignment.h"
#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Memory)

StackAllocator::StackAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize)
	: AllocatorBase(a_BaseAddress, a_ByteSize)
	, m_PrevAllocation(0)
	, m_AddressPointer(0)
{
}

StackAllocator::~StackAllocator()
{
	m_PrevAllocation = 0;
	m_AddressPointer = 0;
}

void* StackAllocator::Allocate(size_t a_Size, uint8_t a_Alignment)
{
	AssertMessage(0 != a_Size, "Invalid size to allocate!");
	AssertMessage(0 == a_Alignment, "Invalid alignment requested!");
	const uint8_t adjustment = AlignmentAdjustment(m_AddressPointer, a_Alignment, sizeof(AllocationHeader));

	uintptr_t alignedAddress = 0;
	if (m_MemoryAllocated + adjustment + a_Size <= m_ByteSize)
	{
		alignedAddress = m_AddressPointer + adjustment;

		AllocationHeader* header = reinterpret_cast<AllocationHeader*>(alignedAddress - sizeof(AllocationHeader));
		header->m_Adjustment = adjustment;
		header->m_PrevAllocation = m_PrevAllocation;
		m_PrevAllocation = alignedAddress;

		m_AddressPointer = alignedAddress + a_Size;
		m_MemoryAllocated += a_Size + adjustment;
		m_NumAllocations++;
	}

	return reinterpret_cast<void*>(alignedAddress);
}

void StackAllocator::Deallocate(void *a_Ptr)
{
	AssertMessage(reinterpret_cast<uintptr_t>(a_Ptr) == m_PrevAllocation, "Invalid pointer to deallocate in stack allocator!");

	AllocationHeader* header = reinterpret_cast<AllocationHeader*>(reinterpret_cast<uintptr_t>(a_Ptr) - sizeof(AllocationHeader));
	m_MemoryAllocated -= m_AddressPointer - reinterpret_cast<uintptr_t>(a_Ptr) + header->m_Adjustment;
	m_AddressPointer = reinterpret_cast<uintptr_t>(a_Ptr) - header->m_Adjustment;

	m_PrevAllocation = header->m_PrevAllocation;
	m_NumAllocations--;
}

#if !defined(NDEBUG)
void StackAllocator::CheckCoherence()
{
	AssertMessage("Checking coherence of stack allocator not implemented!");
}
#endif

END_NAMESPACE(Memory)
