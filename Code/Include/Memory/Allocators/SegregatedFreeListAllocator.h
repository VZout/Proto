#pragma once

#include "AllocatorBase.h"
#include "EMechanism.h"
// #include "MemoryPool.h"
// #include "Utility/Datastructures/OrderedList.h"

BEGIN_NAMESPACE(Memory)

struct MemoryChunk;

class SegregatedFreeListAllocator : public AllocatorBase
{
public:
	SegregatedFreeListAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize);
	virtual ~SegregatedFreeListAllocator();

	virtual void* Allocate(size_t a_Size, uint8_t a_Alignment) override;
	virtual void Deallocate(void *a_Ptr) override;

private:
// 	typedef Utility::OrderedList<MemoryChunk*> FreeList;
// 	FreeList m_FreeList;
// 
// 	MemoryChunk* FindFirstChunk(size_t a_RequestedSize, uint8_t a_Alignment, uint8_t &a_Adjustment);
// 	void SplitChunk(MemoryChunk *a_MemoryChunk, size_t a_RequestedSize);
// 	void CoalesceChunks(MemoryChunk *a_Lhs, MemoryChunk *a_Rhs);
// 
// 	EMechanism m_Mechanism;

// 	friend class MemoryPool<SegregatedFreeListAllocator>;
};

END_NAMESPACE(Memory)
