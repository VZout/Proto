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
	IMemoryPool *memoryPool = NULLPTR;
	switch (a_Allocator)
	{
#if defined(PROTO_CPP03)
	case FreeList:
#else
	case Memory::EAllocator::FreeList:
#endif
		{
			memoryPool = new MemoryPool<FreeListAllocator>(a_ByteSize, a_Mechanism);
			break;
		}
#if defined(PROTO_CPP03)
	case Linear:
	case Pool:
	case SegragatedFreeList:
	case Stack:
#else
	case Memory::EAllocator::Linear:
	case Memory::EAllocator::Pool:
	case Memory::EAllocator::SegragatedFreeList:
	case Memory::EAllocator::Stack:
#endif
	default:
		{
			AssertMessage("Invalid allocatortype requested!");
			break;
		}
	}
	AssertMessage(NULLPTR != memoryPool, "Failed to create new memorypool!");
	return memoryPool;
}

IMemoryPool* CreateMemoryPool(uint64_t a_ByteSize, EAllocator a_Allocator, uint16_t a_ObjectSize /* = 16 */)
{
	IMemoryPool *memoryPool = NULLPTR;
	switch (a_Allocator)
	{
#if defined(PROTO_CPP03)
	case FreeList:
#else
	case EAllocator::FreeList:
#endif
		{
			memoryPool = new MemoryPool<FreeListAllocator>(a_ByteSize);
			break;
		}
#if defined(PROTO_CPP03)
	case Linear:
#else
	case EAllocator::Linear:
#endif
		{
			memoryPool = new MemoryPool<LinearAllocator>(a_ByteSize);
			break;
		}
#if defined(PROTO_CPP03)
	case Pool:
#else
	case EAllocator::Pool:
#endif
		{
			memoryPool = new MemoryPool<PoolAllocator>(a_ByteSize, a_ObjectSize);
			break;
		}
#if defined(PROTO_CPP03)
	case Stack:
#else
	case EAllocator::Stack:
#endif
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
	AssertMessage(NULLPTR != memoryPool, "Failed to create new memorypool!");
	return memoryPool;
}

END_NAMESPACE(Memory)
