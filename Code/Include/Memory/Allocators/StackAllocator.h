#pragma once

#include "AllocatorBase.h"
#include "EAllocator.h"

BEGIN_NAMESPACE(Memory)

class StackAllocator : public AllocatorBase
{
public:
	StackAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize);
	virtual ~StackAllocator();

	virtual void* Allocate(size_t a_Size, uint8_t a_Alignment) OVERRIDE;
	virtual void Deallocate(void *a_Ptr) OVERRIDE;

#if !defined(NDEBUG)
	virtual void CheckCoherence() OVERRIDE;
#endif

private:
	struct AllocationHeader
	{
		uintptr_t m_PrevAllocation;
		uint8_t m_Adjustment;
	};

	uintptr_t m_PrevAllocation;
	uintptr_t m_AddressPointer;
};

END_NAMESPACE(Memory)
