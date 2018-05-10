#include "LinearAllocator.h"

#include "Memory/Helpers/Alignment.h"
#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Memory)

LinearAllocator::LinearAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize)
	: AllocatorBase(a_BaseAddress, a_ByteSize)
	, m_AddressPointer(a_BaseAddress)
{
	AssertMessage(0 != m_BaseAddress, "Invalid base address passed to linear allocator!");
}

LinearAllocator::~LinearAllocator()
{ 
	m_AddressPointer = 0;
}

void* LinearAllocator::Allocate(size_t a_Size, uint8_t a_Alignment)
{
	AssertMessage(0 != a_Size, "Invalid size to allocate!");
	AssertMessage(0 != a_Alignment, "Invalid alignment requested!");

	const uint8_t adjustment = AlignmentAdjustment(m_AddressPointer, a_Alignment);
	uintptr_t alignedAddress = 0;
	if (m_MemoryAllocated + adjustment + a_Size <= m_ByteSize)
	{
		alignedAddress = m_AddressPointer + adjustment;

		m_AddressPointer = alignedAddress + a_Size;
		m_MemoryAllocated += (a_Size + adjustment);
		m_NumAllocations++;
	}

	return reinterpret_cast<void*>(alignedAddress);
}

void LinearAllocator::Deallocate(void *a_Ptr)
{
	AssertMessage("Deallocation for linear allocator not supported (use LinearAllocator::Clear())!");
	UNUSED(a_Ptr);
}

void LinearAllocator::Clear()
{
	m_NumAllocations = 0;
	m_MemoryAllocated = 0;
	m_AddressPointer = static_cast<uintptr_t>(m_BaseAddress);
}

#if !defined(NDEBUG)
void LinearAllocator::CheckCoherence()
{
	AssertMessage("Checking coherence of linear allocator not implemented!");
}
#endif

END_NAMESPACE(Memory)
