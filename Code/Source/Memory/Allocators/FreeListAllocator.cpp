#include "FreeListAllocator.h"

#include "Alignment.h"
#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Memory)

FreeListAllocator::FreeListAllocator(uintptr_t a_BaseAddress, uint64_t a_ByteSize)
	: AllocatorBase(a_BaseAddress, a_ByteSize)
{
	AssertMessage(sizeof(FreeBlock) < a_ByteSize, "Allocated memory block size is too small for a free list allocator!");
	m_FreeList = reinterpret_cast<FreeBlock*>(m_BaseAddress);
	m_FreeList->m_Size = a_ByteSize;
}

FreeListAllocator::~FreeListAllocator()
{
	m_FreeList = nullptr;
}

void* FreeListAllocator::Allocate(size_t a_Size, uint8_t a_Alignment)
{
	AssertMessage(0 != a_Size, "Invalid size to allocate!");
	AssertMessage(0 == a_Alignment, "Invalid alignment requested!");

	FreeBlock *prevFreeBlock = nullptr;
	FreeBlock *freeBlock = m_FreeList;
	while (nullptr != freeBlock)
	{
		const uint8_t adjustment = AlignmentAdjustment(reinterpret_cast<uintptr_t>(freeBlock), a_Alignment, sizeof(AllocationHeader));
		size_t totalSize = a_Size + adjustment;
		if (freeBlock->m_Size < totalSize)
		{
			prevFreeBlock = freeBlock;
			freeBlock = freeBlock->m_Next;
			continue;
		}

		if (freeBlock->m_Size - totalSize <= sizeof(AllocationHeader))
		{
			totalSize = freeBlock->m_Size;
			if (nullptr != prevFreeBlock)
			{
				prevFreeBlock->m_Next = freeBlock->m_Next;
			}
			else
			{
				m_FreeList = freeBlock->m_Next;
			}
		}
		else
		{
			FreeBlock* nextBlock = reinterpret_cast<FreeBlock*>(reinterpret_cast<uintptr_t>(freeBlock) + totalSize);
			nextBlock->m_Size = freeBlock->m_Size = totalSize;
			nextBlock->m_Next = freeBlock->m_Next;
			if (nullptr != prevFreeBlock)
			{
				prevFreeBlock->m_Next = nextBlock;
			}
			else
			{
				m_FreeList = nextBlock;
			}
		}

		uintptr_t alignedAddress = reinterpret_cast<uintptr_t>(freeBlock) + adjustment;
		AllocationHeader* header = reinterpret_cast<AllocationHeader*>(alignedAddress - sizeof(AllocationHeader));
		header->m_BlockSize = totalSize;
		header->m_Adjustment = adjustment;
		m_MemoryAllocated += totalSize;
		m_NumAllocations++;

		AssertMessage(0 == AlignmentAdjustment(alignedAddress, a_Alignment), "Allocation address incorrectly aligned!");
		return reinterpret_cast<void*>(alignedAddress);
	}
	AssertMessage("Could not allocate free block!");
	return nullptr;
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

END_NAMESPACE(Memory)
