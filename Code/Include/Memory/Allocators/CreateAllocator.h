#pragma once

#include "EAllocator.h"
#include "Allocators/PoolAllocator.h"

BEGIN_NAMESPACE(Memory)

template<class ALLOCATOR>
ALLOCATOR* CreateAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize)
{
	return new ALLOCATOR(a_BaseAddress, a_ByteSize);
}

// template<class ALLOCATOR>
// ALLOCATOR* CreateAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize, uint16_t a_ObjectSize = 16)
// {
// 	UNUSED(a_ObjectSize);
// 	return new ALLOCATOR(a_BaseAddress, a_ByteSize);
// }

template<class ALLOCATOR>
inline ALLOCATOR* CreateAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize, uint16_t a_ObjectSize /* = 16 */)
{
	return new ALLOCATOR(a_BaseAddress, a_ByteSize, a_ObjectSize);
}

END_NAMESPACE(Memory)
