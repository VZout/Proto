 #include "CreateMemoryPool.h"

#include "Allocators/FreeListAllocator.h"
#include "Allocators/LinearAllocator.h"
#include "Allocators/PoolAllocator.h"
#include "Allocators/StackAllocator.h"
#include "MemoryPool.h"
#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Memory)

IMemoryPool* CreateMemoryPool(uint64_t a_ByteSize, EAllocator a_Allocator, EMechanism a_Mechanism)
{
	IMemoryPool *memoryPool = nullptr;
	const uint16_t objectSize = 16;
	memoryPool = new MemoryPool<FreeListAllocator>(a_ByteSize, a_Mechanism);
	AssertMessage(nullptr != memoryPool, "Failed to create new memorypool!");
	return memoryPool;
}

IMemoryPool* CreateMemoryPool(uint64_t a_ByteSize, EAllocator a_Allocator, uint16_t a_ObjectSize /* = 16 */)
{
	IMemoryPool *memoryPool = nullptr;
	switch (a_Allocator)
	{
	case EAllocator::FreeList:
		{
			memoryPool = new MemoryPool<FreeListAllocator>(a_ByteSize);
			break;
		}
	case EAllocator::Linear:
		{
			memoryPool = new MemoryPool<LinearAllocator>(a_ByteSize);
			break;
		}
	case EAllocator::Pool:
		{
			memoryPool = new MemoryPool<PoolAllocator>(a_ByteSize, a_ObjectSize);
			break;
		}
	case EAllocator::Stack:
		{
			memoryPool = new MemoryPool<StackAllocator>(a_ByteSize);
			break;
		}
	default:
		{
			AssertMessage("Invalid allocatortype requested!");
			break;
		}
	}
	AssertMessage(nullptr != memoryPool, "Failed to create new memorypool!");
	return memoryPool;
}

END_NAMESPACE(Memory)
