#pragma once

#include "AllocatorBase.h"
#include "EAllocator.h"

BEGIN_NAMESPACE(Memory)

class StackAllocator : public AllocatorBase
{
public:
	StackAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize);
	virtual ~StackAllocator();

	virtual void* Allocate(size_t a_Size, uint8_t a_Alignment) override;
	virtual void Deallocate(void *a_Ptr) override;

private:
	struct AllocationHeader
	{
		uintptr_t m_PrevAllocation = 0;
		uint8_t m_Adjustment = 0;
	};

	uintptr_t m_PrevAllocation = 0;
	uintptr_t m_AddressPointer = 0;
};

END_NAMESPACE(Memory)
