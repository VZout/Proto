#pragma once

#include "AllocatorBase.h"
#include "EAllocator.h"

BEGIN_NAMESPACE(Memory)

class PoolAllocator : public AllocatorBase
{
public:
	PoolAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize, uint16_t a_ObjectSize);
	virtual ~PoolAllocator();

	virtual void* Allocate(size_t a_Size, uint8_t a_Alignment) OVERRIDE;
	virtual void Deallocate(void *a_Ptr) OVERRIDE;

#if !defined(NDEBUG)
	virtual void CheckCoherence() OVERRIDE;
#endif

private:
	const uint16_t m_ObjectSize;
	uint8_t m_Alignment;
	void **m_FreeList;
};

END_NAMESPACE(Memory)
