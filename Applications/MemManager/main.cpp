#include "Proto.h"

#include "Classes.h"

#include "Memory/Allocators/FreeListAllocator.h"
#include "Memory/Helpers/Alignment.h"
#include "Memory/CreateMemoryPool.h"
#include "Memory/Memory.h"
#include "Memory/MemoryPool.h"
#include "Memory/Allocators/LinearAllocator.h"
#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Memory)
USING_NAMESPACE(Platform)

uint64_t CalculatePointerDistance(void *a_Lhs, void *a_Rhs)
{
	return static_cast<uint64_t>(reinterpret_cast<uintptr_t>(a_Rhs) - reinterpret_cast<uintptr_t>(a_Lhs));
}

void TestFreeListAllocator()
{
	IMemoryPool &memoryPool = *CreateMemoryPool(BYTES(256), EAllocator::FreeList, EMechanism::FirstFit);

	const uint8_t alignment = 16;
	TestClass<4> *a = ALIGNED_NEW(memoryPool, TestClass<4>, alignment);
	AssertMessage(IsAligned(a, alignment), "Invalid alignment!");
	DEL(a, memoryPool);

	TestClass<8> *b = ALIGNED_NEW(memoryPool, TestClass<8>, alignment);
	AssertMessage(IsAligned(b, alignment), "Invalid alignment!");

	TestClass<12> *c = ALIGNED_NEW(memoryPool, TestClass<12>, alignment);
	AssertMessage(IsAligned(c, alignment), "Invalid alignment!");

	TestClass<200> *d = ALIGNED_NEW(memoryPool, TestClass<200>, alignment);
	AssertMessage(IsAligned(d, alignment), "Invalid alignment!");

	memoryPool.CheckCoherence();

	DEL(b, memoryPool);
}

void TestLinearAllocator()
{
	IMemoryPool &memoryPool = *CreateMemoryPool(MB(256), EAllocator::Linear);
	LinearAllocator &allocator = static_cast<LinearAllocator&>(memoryPool.GetAllocator());

	TestClass<4> *a = NEW(memoryPool, TestClass<4>);
	TestClass<4> *b = NEW(memoryPool, TestClass<4>);
	allocator.Clear();

	a = ALIGNED_NEW(memoryPool, TestClass<4>, 16);
	b = ALIGNED_NEW(memoryPool, TestClass<4>, 16);

	TestClass<20> *c = NEW(memoryPool, TestClass<20>);
	TestClass<20> *d = NEW(memoryPool, TestClass<20>);
	allocator.Clear();

	c = ALIGNED_NEW(memoryPool, TestClass<20>, 16);
	d = ALIGNED_NEW(memoryPool, TestClass<20>, 16);
}

void TestPoolAllocator()
{
	IMemoryPool &memoryPool = *CreateMemoryPool(MB(256), EAllocator::Pool);
	UNUSED(memoryPool);
}

void TestStackAllocator()
{
	IMemoryPool &memoryPool = *CreateMemoryPool(MB(256), EAllocator::Stack);
	UNUSED(memoryPool);
}

USING_NAMESPACE(Utility)
int main(int a_ArgC, const char * a_ArgV[])
{
	UNUSED(a_ArgC);
	UNUSED(a_ArgV);

	TestFreeListAllocator();
	TestLinearAllocator();
	TestPoolAllocator();
	TestStackAllocator();

	return 0;
}
