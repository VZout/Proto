#pragma once

#include "AllocatorBase.h"
#include "EAllocator.h"
#include "EMechanism.h"
#include "Utility/Datastructures/OrderedList.h"

BEGIN_NAMESPACE(Memory)

template<typename T>
class MemoryPool;

struct MemoryChunk;

class FreeListAllocator : public AllocatorBase
{
public:
	FreeListAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize);
	virtual ~FreeListAllocator();

	virtual void* Allocate(size_t a_Size, uint8_t a_Alignment) OVERRIDE;
	virtual void Deallocate(void *a_Ptr) OVERRIDE;

#if !defined(NDEBUG)
	virtual void CheckCoherence() OVERRIDE;
#endif

private:
	typedef Utility::OrderedList<MemoryChunk*> FreeList;
	FreeList m_FreeList;

	MemoryChunk* FindFirstChunk(size_t a_RequestedSize, uint8_t a_Alignment, uint8_t &a_Adjustment);
	void SplitChunk(MemoryChunk *a_MemoryChunk, size_t a_RequestedSize);
	void CoalesceChunks(MemoryChunk *a_Lhs, MemoryChunk *a_Rhs);

	EMechanism m_Mechanism;

	friend class MemoryPool<FreeListAllocator>;	
};

END_NAMESPACE(Memory)
