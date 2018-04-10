#pragma once

#include "AllocatorBase.h"
#include "EAllocator.h"

BEGIN_NAMESPACE(Memory)

class LinearAllocator : public AllocatorBase
{
public:
	LinearAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize);
	virtual ~LinearAllocator();

	virtual void* Allocate(size_t a_Size, uint8_t a_Alignment) override;
	virtual void Deallocate(void *a_Ptr) override;
	
	void Clear();

private:
	uintptr_t m_AddressPointer = 0;
};

END_NAMESPACE(Memory)
