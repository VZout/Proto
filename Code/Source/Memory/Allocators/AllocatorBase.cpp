#include "AllocatorBase.h"

#include "Math/Max.h"
#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Math)
USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Memory)

AllocatorBase::AllocatorBase(uintptr_t a_BaseAddress, uint64_t a_ByteSize)
	: m_BaseAddress(a_BaseAddress)
	, m_ByteSize(a_ByteSize)
	, m_NumAllocations(0)
	, m_MemoryAllocated(0)
	, m_PeakAllocation(0)
{
}

AllocatorBase::~AllocatorBase()
{
}

void AllocatorBase::ValidatePointer(void *a_Ptr)
{
#if !defined(NDEBUG)
	const uintptr_t dataAddress = reinterpret_cast<uintptr_t>(a_Ptr);
	AssertMessage(dataAddress >= m_BaseAddress && dataAddress <= (m_BaseAddress + m_ByteSize), "Pointer has not been allocated by this allocator!");
#endif
}

void AllocatorBase::UpdateAllocations(size_t a_Size)
{
	m_MemoryAllocated += a_Size;
	m_PeakAllocation = Max(m_PeakAllocation, m_MemoryAllocated);
	m_NumAllocations++;
}

void AllocatorBase::UpdateDeallocations(size_t a_Size)
{
	m_MemoryAllocated -= a_Size;
	m_NumAllocations--;
}

END_NAMESPACE(Memory)
