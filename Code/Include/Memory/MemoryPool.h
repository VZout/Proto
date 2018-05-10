#pragma once

#include "Allocators/CreateAllocator.h"
#include "Allocators/FreeListAllocator.h"
#include "IMemoryPool.h"
#include "Platform/Debug/AssertMessage.h"

#if !defined(NDEBUG)
#include <iostream>
#endif

BEGIN_NAMESPACE(Memory)

template<class ALLOCATOR>
class MemoryPool : public IMemoryPool
{
public:
	MemoryPool(uint64_t a_ByteSize)
		: m_Allocator(NULLPTR)
		, m_ByteSize(a_ByteSize)
	{
		InitializeMemoryBlob();
		m_Allocator = CreateAllocator<ALLOCATOR>(reinterpret_cast<uintptr_t>(m_BaseAddress), a_ByteSize);
		Platform::AssertMessage(NULLPTR != m_Allocator, "Failed to create allocator!");
	}

	MemoryPool(uint64_t a_ByteSize, EMechanism a_Mechanism)
		: m_ByteSize(a_ByteSize)
	{
		InitializeMemoryBlob();
		m_Allocator = CreateAllocator<FreeListAllocator>(reinterpret_cast<uintptr_t>(m_BaseAddress), a_ByteSize);
		Platform::AssertMessage(NULLPTR != m_Allocator, "Failed to create allocator!");

		FreeListAllocator &freeListAllocator = static_cast<FreeListAllocator&>(*m_Allocator);
		freeListAllocator.m_Mechanism = a_Mechanism;
	}

	MemoryPool(uint64_t a_ByteSize, uint16_t a_ObjectSize)
		: m_ByteSize(a_ByteSize)
	{
		InitializeMemoryBlob();
		m_Allocator = CreateAllocator<PoolAllocator>(reinterpret_cast<uintptr_t>(m_BaseAddress), a_ByteSize, a_ObjectSize);
		Platform::AssertMessage(NULLPTR != m_Allocator, "Failed to create pool allocator!");
	}

	void InitializeMemoryBlob()
	{
		Platform::AssertMessage(0 != m_ByteSize, "Invalid memory pool size encountered!");		
		m_BaseAddress = ::malloc(static_cast<size_t>(m_ByteSize));
		Platform::AssertMessage(NULLPTR != m_BaseAddress, "Failed to allocate memory pool!");
	}

	virtual ~MemoryPool()
	{
		::free(m_BaseAddress);
	}

	virtual void* Allocate(size_t a_Size, uint8_t a_Alignment) OVERRIDE
	{
		void *address = m_Allocator->Allocate(a_Size, a_Alignment);
		Platform::AssertMessage(NULLPTR != address, "Failed to allocate memory!");
		return address;
	}

	virtual void Deallocate(void *a_Ptr) OVERRIDE
	{
		m_Allocator->Deallocate(a_Ptr);
	}

	IAllocator& GetAllocator() OVERRIDE
	{
		Platform::AssertMessage(NULLPTR != m_Allocator, "Attempt to retrieve an invalid allocator!");
		return *m_Allocator;
	}

#if !defined(NDEBUG)
	void CheckCoherence() OVERRIDE
	{
		Platform::AssertMessage(NULLPTR != m_Allocator, "Attempt to use an invalid allocator!");
		m_Allocator->CheckCoherence();
		std::cout << "Memory pool coherence check success!" << std::endl;
	}
#endif

private:
	ALLOCATOR *m_Allocator;
	void *m_BaseAddress;
	const uint64_t m_ByteSize;
};

END_NAMESPACE(Memory)
