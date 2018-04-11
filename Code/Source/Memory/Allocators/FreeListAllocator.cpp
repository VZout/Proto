#include "FreeListAllocator.h"

#include "Alignment.h"
#include "Helpers/MemoryChunkHelpers.h"
#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Memory)

struct MemoryChunk
{
#if defined(_DEBUG)
	uint32_t m_Guard;
#endif
	size_t m_Size;
	bool m_Used;
};

BEGIN_UNNAMEDNAMESPACE()

#if defined(_DEBUG)

void SetMemoryChunkHeaderGuard(MemoryChunk *a_Chunk)
{
	AssertMessage(nullptr != a_Chunk, "Invalid chunk encountered while setting chunk header guard value.");
	a_Chunk->m_Guard = g_HeaderGuardValue;
}

void CheckMemoryChunkHeaderGuard(MemoryChunk *a_Chunk)
{
	AssertMessage(nullptr != a_Chunk, "Invalid chunk encountered while checking chunk header guard value.");
	AssertMessage(g_HeaderGuardValue == a_Chunk->m_Guard, "Memory chunk has invalid header guard value!");
}

void SetMemoryChunkFooterGuard(MemoryChunk *a_Chunk)
{
	AssertMessage(nullptr != a_Chunk, "Invalid chunk encountered while setting chunk footer guard value.");
	*(reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(a_Chunk) + (a_Chunk->m_Size - sizeof(g_FooterGuardValue)))) = g_FooterGuardValue;
}

void CheckMemoryChunkFooterGuard(MemoryChunk *a_Chunk)
{
	AssertMessage(nullptr != a_Chunk, "Invalid chunk encountered while checking chunk footer guard value.");
	const uint32_t footerGuardValue = *(reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(a_Chunk) + (a_Chunk->m_Size - sizeof(g_FooterGuardValue))));
	AssertMessage(g_FooterGuardValue == footerGuardValue, "Memory chunk has invalid footer guard value!");
}

#endif

MemoryChunk* GetNextChunk(MemoryChunk *a_Chunk)
{
	AssertMessage(nullptr != a_Chunk, "Invalid chunk encountered while getting next chunk.");
	return reinterpret_cast<MemoryChunk*>(reinterpret_cast<uintptr_t>(a_Chunk) + a_Chunk->m_Size);
}

size_t CalculateTotalChunkSize(size_t a_RequestedSize)
{
#if defined(_DEBUG)
	return a_RequestedSize + sizeof(MemoryChunk) + sizeof(g_FooterGuardValue);
#else
	return a_RequestedSize + sizeof(MemoryChunk);
#endif
}

void SplitChunk(MemoryChunk *a_Chunk, size_t a_RequestedSize, uint8_t a_Alignment)
{
	uintptr_t chunk = reinterpret_cast<uintptr_t>(a_Chunk);
	uint8_t alignmentAdjustment = AlignmentAdjustment(chunk + sizeof(MemoryChunk), a_Alignment);
	const size_t totalChunkSize = CalculateTotalChunkSize(a_RequestedSize) + alignmentAdjustment;
	MemoryChunk *newChunk = reinterpret_cast<MemoryChunk*>(chunk + totalChunkSize);
	newChunk->m_Size = a_Chunk->m_Size - totalChunkSize;
	newChunk->m_Used = false;
	a_Chunk->m_Size = totalChunkSize;

#if defined(_DEBUG)
	SetMemoryChunkFooterGuard(a_Chunk);
	SetMemoryChunkHeaderGuard(newChunk);
#endif
}

END_UNNAMEDNAMESPACE()

FreeListAllocator::FreeListAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize)
	: AllocatorBase(a_BaseAddress, a_ByteSize)
{
	AssertMessage(sizeof(MemoryChunk) + sizeof(uint32_t) < a_ByteSize, "Allocated memory block size is too small for a free list allocator!");
	m_FreeList = reinterpret_cast<MemoryChunk*>(m_BaseAddress);
	m_FreeList->m_Size = a_ByteSize;
	m_FreeList->m_Used = false;
#if defined(_DEBUG)
	SetMemoryChunkHeaderGuard(m_FreeList);
	SetMemoryChunkFooterGuard(m_FreeList);
#endif
}

FreeListAllocator::~FreeListAllocator()
{
	m_FreeList = nullptr;
}

void* FreeListAllocator::Allocate(size_t a_Size, uint8_t a_Alignment)
{
	AssertMessage(0 != a_Size, "Invalid size to allocate!");
	AssertMessage(0 != a_Alignment, "Invalid alignment requested!");

	void *chunk = FindFirstChunk(a_Size, a_Alignment);
	AssertMessage(nullptr != chunk, "Unable to allocate requested chunk size!");
	void *dataPointer = AlignAddress(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(chunk) + sizeof(MemoryChunk)), a_Alignment);
	return dataPointer;
}

void FreeListAllocator::Deallocate(void *a_Ptr)
{
	AssertMessage(nullptr != a_Ptr, "Attempt to deallocate an invalid pointer!");
/*
  AllocationHeader* header = (AllocationHeader*)pointer_math::subtract(p, sizeof(AllocationHeader)); 
  uptr block_start = reinterpret_cast<uptr>(p) - header->adjustment; 
  size_t block_size = header->size; 
  uptr block_end = block_start + block_size; 
  FreeBlock* prev_free_block = nullptr; 
  FreeBlock* free_block = _free_blocks; 
  
  while(free_block != nullptr) 
  {
    if( (uptr) free_block >= block_end ) break; 
    prev_free_block = free_block; 
    free_block = free_block->next;
  }
  
  if(prev_free_block == nullptr) 
  {
    prev_free_block = (FreeBlock*) block_start; 
    prev_free_block->size = block_size; 
    prev_free_block->next = _free_blocks; 
    _free_blocks = prev_free_block; 
  }
  else if((uptr) prev_free_block + prev_free_block->size == block_start) 
  {
    prev_free_block->size += block_size; 
  }
  else 
  {
    FreeBlock* temp = (FreeBlock*) block_start; 
    temp->size = block_size; 
    temp->next = prev_free_block->next; 
    prev_free_block->next = temp; 
    prev_free_block = temp; 
  }
  
  if( free_block != nullptr && (uptr) free_block == block_end) 
  {
    prev_free_block->size += free_block->size; 
    prev_free_block->next = free_block->next;
  }
  
  _num_allocations--; 
  _used_memory -= block_size; 
  */
}

#if defined(_DEBUG)
void FreeListAllocator::CheckCoherence()
{
	MemoryChunk *chunk = m_FreeList;
	while (nullptr != chunk)
	{
		CheckMemoryChunkHeaderGuard(chunk);
		CheckMemoryChunkFooterGuard(chunk);

		const uintptr_t chunkEnd = reinterpret_cast<uintptr_t>(chunk) + chunk->m_Size;
		static const uintptr_t maxPoolAddress = m_BaseAddress + m_ByteSize;
		if (chunkEnd > maxPoolAddress)
		{
			AssertMessage(chunkEnd <= m_BaseAddress + m_ByteSize, "Chunk extends beyond the size of the memory pool!");
		}
		else if (chunkEnd == maxPoolAddress)
		{
			break;
		}
		
		chunk = GetNextChunk(chunk);
	}
}
#endif

void* FreeListAllocator::FindFirstChunk(size_t a_RequestedSize, uint8_t a_Alignment)
{
	MemoryChunk *chunk = m_FreeList;

	while (chunk->m_Used || chunk->m_Size < a_RequestedSize)
	{
		chunk = GetNextChunk(chunk);
	}

	if (chunk->m_Size > a_RequestedSize)
	{
		SplitChunk(chunk, a_RequestedSize, a_Alignment);
		AssertMessage(a_RequestedSize <= chunk->m_Size, "Splitting memory chunk led to unexpected size result!");
	}

	return chunk;
}

END_NAMESPACE(Memory)
