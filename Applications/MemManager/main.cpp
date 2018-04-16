#include "Proto.h"

#include "Classes.h"

#include "Memory/Allocators/FreeListAllocator.h"
#include "Memory/Helpers/Alignment.h"
#include "Memory/CreateMemoryPool.h"
#include "Memory/Memory.h"
#include "Memory/MemoryPool.h"
#include "Memory/Allocators/LinearAllocator.h"
#include "Platform/Debug/AssertMessage.h"

#include "Utility/Datastructures/BinarySearchTree.h"
#include "Utility/Datastructures/RedBlackTree.h"
// #include "Utility/Algorithms/TreeTraversals.h"
// #include "Utility/Datastructures/SinglyLinkedList.h"
// #include "Utility/Datastructures/DoublyLinkedList.h"

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

	uint64_t distance = CalculatePointerDistance(a, b);
	AssertMessage(4 == distance, "Invalid pointer distance encountered!");
	allocator.Clear();

	a = ALIGNED_NEW(memoryPool, TestClass<4>, 16);
	b = ALIGNED_NEW(memoryPool, TestClass<4>, 16);
	distance = CalculatePointerDistance(a, b);
	AssertMessage(16 == distance, "Invalid pointer distance encountered!");

	TestClass<20> *c = NEW(memoryPool, TestClass<20>);
	TestClass<20> *d = NEW(memoryPool, TestClass<20>);
	distance = CalculatePointerDistance(c, d);
	AssertMessage(20 == distance, "Invalid pointer distance encountered!");
	allocator.Clear();

	c = ALIGNED_NEW(memoryPool, TestClass<20>, 16);
	d = ALIGNED_NEW(memoryPool, TestClass<20>, 16);
	distance = CalculatePointerDistance(c, d);
	AssertMessage(32 == distance, "Invalid pointer distance encountered!");
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

	BinarySearchTree<int> bt;
	bt.Insert(30);
	bt.Insert(10);
	bt.Insert(40);
	bt.Insert(20);
	bt.Insert(50);

	RedBlackTree<int> rbt;
	rbt.Insert(26);	// checked OK
	rbt.Insert(17);	// checked OK
	rbt.Insert(41);	// checked OK
	rbt.Insert(30);	// checked OK
	rbt.Insert(47);	// checked OK
	rbt.Insert(28);	// checked OK
	rbt.Insert(38);	// checked OK
	rbt.Validate();
	rbt.Insert(35); // tree invalid
	rbt.Insert(39);
	rbt.Insert(14);
	rbt.Insert(21);
	rbt.Insert(10);
	rbt.Insert(16);
	rbt.Insert(19);
	rbt.Insert(23);
	rbt.Insert(7);
	rbt.Insert(12);
	rbt.Insert(15);
	rbt.Insert(20);
	rbt.Insert(3);
	rbt.Validate();

	TestFreeListAllocator();
	TestLinearAllocator();
	TestPoolAllocator();
	TestStackAllocator();

	return 0;
}
