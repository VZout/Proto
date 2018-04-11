#pragma once

#include "AllocatorBase.h"
#include "EAllocator.h"

BEGIN_NAMESPACE(Memory)

class PoolAllocator : public AllocatorBase
{
public:
	PoolAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize, uint16_t a_ObjectSize);
	virtual ~PoolAllocator();

	virtual void* Allocate(size_t a_Size, uint8_t a_Alignment) override;
	virtual void Deallocate(void *a_Ptr) override;

#if defined(_DEBUG)
	virtual void CheckCoherence() override;
#endif

private:
	const uint16_t m_ObjectSize;
	uint8_t m_Alignment = 0;
	void **m_FreeList;
};

END_NAMESPACE(Memory)
