#pragma once

#include "AllocatorBase.h"
#include "EAllocator.h"

BEGIN_NAMESPACE(Memory)

class LinearAllocator : public AllocatorBase
{
public:
	LinearAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize);
	virtual ~LinearAllocator();

	virtual void* Allocate(size_t a_Size, uint8_t a_Alignment) OVERRIDE;
	virtual void Deallocate(void *a_Ptr) OVERRIDE;
	
	void Clear();

#if !defined(NDEBUG)
	virtual void CheckCoherence() OVERRIDE;
#endif

private:
	uintptr_t m_AddressPointer;
};

END_NAMESPACE(Memory)
