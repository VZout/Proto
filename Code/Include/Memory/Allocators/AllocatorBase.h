#pragma once

#include "IAllocator.h"

BEGIN_NAMESPACE(Memory)

class AllocatorBase : public IAllocator
{
public:
	AllocatorBase(uintptr_t a_BaseAddress, uint64_t a_ByteSize);
	virtual ~AllocatorBase();

protected:
	void UpdateAllocations(size_t a_Size);
	void UpdateDeallocations(size_t a_Size);

	const uintptr_t m_BaseAddress;
	const uint64_t m_ByteSize;
	uint32_t m_NumAllocations;
	uint64_t m_MemoryAllocated;
	uint64_t m_PeakAllocation;

	friend class IMemoryPool;
};

END_NAMESPACE(Memory)
