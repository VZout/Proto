#pragma once

#include "Allocators/CreateAllocator.h"
#include "IMemoryPool.h"
#include "Platform/Debug/AssertMessage.h"

BEGIN_NAMESPACE(Memory)

template<class ALLOCATOR>
class MemoryPool : public IMemoryPool
{
public:
	MemoryPool(uint64_t a_ByteSize, uint16_t a_ObjectSize /* = 16 */)
		: m_ByteSize(a_ByteSize)
	{
		Platform::AssertMessage(0 != m_ByteSize, "Invalid memory pool size encountered!");
		m_BaseAddress = ::malloc(m_ByteSize);
		Platform::AssertMessage(nullptr != m_BaseAddress, "Failed to allocate memory pool!");
		m_Allocator = CreateAllocator<ALLOCATOR>(reinterpret_cast<uintptr_t>(m_BaseAddress), a_ByteSize, a_ObjectSize);
		Platform::AssertMessage(nullptr != m_Allocator, "Failed to create allocator!");
	}

	virtual ~MemoryPool()
	{
		::free(m_BaseAddress);
	}

	virtual void* Allocate(size_t a_Size, uint8_t a_Alignment)
	{
		void *address = m_Allocator->Allocate(a_Size, a_Alignment);
		Platform::AssertMessage(nullptr != address, "Failed to allocate memory!");
		return address;
	}

	virtual void Deallocate(void *a_Ptr)
	{
		m_Allocator->Deallocate(a_Ptr);
	}

	IAllocator& GetAllocator()
	{
		Platform::AssertMessage(nullptr != m_Allocator, "Attempt to retrieve an invalid allocator!");
		return *m_Allocator;
	}

private:
	ALLOCATOR *m_Allocator = nullptr;
	void *m_BaseAddress;
	const uint64_t m_ByteSize;
};

END_NAMESPACE(Memory)
