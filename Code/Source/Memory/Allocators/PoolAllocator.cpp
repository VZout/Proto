#include "PoolAllocator.h"

#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Memory)

PoolAllocator::PoolAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize, uint16_t a_ObjectSize)
	: AllocatorBase(a_BaseAddress, a_ByteSize)
	, m_ObjectSize(a_ObjectSize)
{
	AssertMessage(sizeof(void*) < a_ObjectSize, "Invalid object size for pool allocator!");
}

PoolAllocator::~PoolAllocator()
{
	m_FreeList = nullptr;
}

void* PoolAllocator::Allocate(size_t a_Size, uint8_t a_Alignment)
{
	AssertMessage(m_ObjectSize == a_Size, "Invalid object size for this pool allocator!");
	AssertMessage(m_Alignment == a_Alignment, "Invalid object alignment!");

	void *address = nullptr;
	if (nullptr != m_FreeList)
	{
		address = m_FreeList;
		m_FreeList =  reinterpret_cast<void**>(*m_FreeList);
		m_MemoryAllocated += a_Size;
		m_NumAllocations++;
	}
	return reinterpret_cast<void*>(address);
}

void PoolAllocator::Deallocate(void *a_Ptr)
{
	*reinterpret_cast<void**>(a_Ptr) = m_FreeList;
	m_FreeList = reinterpret_cast<void**>(a_Ptr);
	m_MemoryAllocated -= m_ObjectSize;
	m_NumAllocations--;
}

END_NAMESPACE(Memory)
