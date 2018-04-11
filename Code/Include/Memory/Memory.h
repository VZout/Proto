#pragma once

#include "IMemoryPool.h"

#define BYTES(x) static_cast<uint64_t>((x))
#define KB(x) static_cast<uint64_t>((x) << 10)
#define MB(x) static_cast<uint64_t>((x) << 20)
#define GB(x) static_cast<uint64_t>((x) << 30)

static const uint64_t gs_ByteSize = 1;
static const uint64_t gs_KiloByteSize = 1024;
static const uint64_t gs_MegaByteSize = 1024 * 1024;
static const uint64_t gs_GigaByteSize = 1024 * 1024 * 1024;

inline void* operator new(size_t a_Size, Memory::IMemoryPool *a_Pool, uint8_t a_Alignment = 4)
{
	return a_Pool->Allocate(a_Size, a_Alignment);
}

inline void operator delete(void*, Memory::IMemoryPool*) { }

BEGIN_NAMESPACE(Memory)

template<class TYPE>
void PlacementDelete(TYPE *a_Ptr, IMemoryPool *a_Pool)
{
	if (a_Ptr)
	{
		a_Ptr->~TYPE();
		a_Pool->Deallocate(a_Ptr);
	}
}

END_NAMESPACE(Memory)

#undef DEL
#define NEW(MEM_POOL, TYPE) new(&MEM_POOL) TYPE()
#define ALIGNED_NEW(MEM_POOL, TYPE, ALIGNMENT) new(&MEM_POOL, ALIGNMENT) TYPE()
#define DEL(POINTER, MEM_POOL) Memory::PlacementDelete(POINTER, &MEM_POOL)

// resources:
// https://www.gamedev.net/articles/programming/general-and-gameplay-programming/c-custom-memory-allocation-r3010/
