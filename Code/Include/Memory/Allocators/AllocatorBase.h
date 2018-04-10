#pragma once

#include "IAllocator.h"

BEGIN_NAMESPACE(Memory)

class AllocatorBase : public IAllocator
{
public:
	AllocatorBase(uintptr_t a_BaseAddress, uint64_t a_ByteSize);
	virtual ~AllocatorBase();

protected:
	const uintptr_t m_BaseAddress;
	const uint64_t m_ByteSize;
	uint32_t m_NumAllocations = 0;
	uint64_t m_MemoryAllocated = 0;

	friend class IMemoryPool;
};

END_NAMESPACE(Memory)
