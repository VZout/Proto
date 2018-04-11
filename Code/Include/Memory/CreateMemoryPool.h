#pragma once

#include "EAllocator.h"
#include "EMechanism.h"

BEGIN_NAMESPACE(Memory)

class IMemoryPool;
IMemoryPool* CreateMemoryPool(uint64_t a_ByteSize, EAllocator a_Allocator, EMechanism a_Mechanism);
IMemoryPool* CreateMemoryPool(uint64_t a_ByteSize, EAllocator a_Allocator, uint16_t a_ObjectSize = 16);

END_NAMESPACE(Memory)
