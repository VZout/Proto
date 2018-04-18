#pragma once

#include "AllocatorBase.h"
#include "EAllocator.h"
#include "EMechanism.h"
#include "MemoryPool.h"
#include "Utility/Datastructures/OrderedList.h"

BEGIN_NAMESPACE(Memory)

struct MemoryChunk;

class FreeListAllocator : public AllocatorBase
{
public:
	FreeListAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize);
	virtual ~FreeListAllocator();

	virtual void* Allocate(size_t a_Size, uint8_t a_Alignment) override;
	virtual void Deallocate(void *a_Ptr) override;

#if defined(_DEBUG)
	virtual void CheckCoherence() override;
#endif

private:
	typedef Utility::OrderedList<MemoryChunk*> FreeList;
	FreeList m_FreeList;

	MemoryChunk* FindFirstChunk(size_t a_RequestedSize, uint8_t a_Alignment, uint8_t &a_Adjustment);
	void SplitChunk(MemoryChunk *a_MemoryChunk, size_t a_RequestedSize);

	EMechanism m_Mechanism;

	friend class MemoryPool<FreeListAllocator>;	
};

END_NAMESPACE(Memory)
