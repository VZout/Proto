#include "AllocatorBase.h"

#include "Math/Max.h"

USING_NAMESPACE(Math)

BEGIN_NAMESPACE(Memory)

AllocatorBase::AllocatorBase(uintptr_t a_BaseAddress, uint64_t a_ByteSize)
	: m_BaseAddress(a_BaseAddress)
	, m_ByteSize(a_ByteSize)
{
}

AllocatorBase::~AllocatorBase()
{
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
